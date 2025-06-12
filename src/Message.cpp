#include "JT808/Message.h"
#include "JT808/BCD.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/MessageBodyFactory.h"
#include "JT808/MessageIds.h"
#include "JT808/Schema/MessageSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

namespace JT808 {

enum MessageDef : uint8_t
{
    MinimumMsgSize = 15, // 1 (begin marker) + 12 (header no pkg) + 1 (checksum) + 1 (end marker)
    HeaderPos = 1,
    HeaderNoPacketSize = 12,
    HeaderPacketSize = 16,
    BodyNoPacketPos = HeaderPos + HeaderNoPacketSize,
    BodyPacketPos = HeaderPos + HeaderPacketSize,
};

Message::Message()
{
    m_validator.set_root_schema(Schema::MessageSchema);
}

Message::Message(Header header, std::unique_ptr<MessageBody::MessageBodyBase> body)
    : m_header(std::move(header))
    , m_body(std::move(body))
{
    m_validator.set_root_schema(Schema::MessageSchema);
}

void Message::fromJson(const Json& data)
{
    if (validateJson(data)) {
        m_header.fromJson(data["header"]);
        m_body = MessageBody::MessageBodyFactory::create(MessageIds(m_header.id));
        m_body->fromJson(data.value("body", Json::object({})));
        m_isValid = m_body->isValid();
    } else {
        m_isValid = false;
    }
}

Json Message::toJson()
{
    return Json::object({{"header", m_header.toJson()}, {"body", m_body->toJson()}});
}

ByteArray Message::package()
{
    ByteArray result;

    // package body
    ByteArray const bodyRawData(packageBody());
    // modify body len in header
    m_header.bodyProps.bits.len = bodyRawData.size();
    // header
    Utils::append(packageHeader(), result);
    // insert body
    Utils::append(bodyRawData, result);
    // checksum
    m_checksum = Utils::calculateChecksum(result.data(), result.size());
    result.push_back(m_checksum);

    // escape
    result = Utils::escape(result);
    // begin flag
    result.insert(result.begin(), Utils::ProtocolSign);
    // protocol sign
    result.push_back(Utils::ProtocolSign);

    return result;
}

void Message::parse(const ByteArray& data)
{
    ByteArray output = Utils::reverseEscape(data);
    m_checksum = Utils::calculateChecksum(output.data() + HeaderPos, output.size() - 3);
    validateChecksum(*(output.end() - 2));

    if (!m_isValid)
        return;

    if (!parseHeader(output)) {
        m_isValid = false;
        return;
    }

    if (!parseBody(output)) {
        m_isValid = false;
        return;
    }

    m_isValid = true;
}

void Message::validateChecksum(uint8_t checksum)
{
    m_isValid = m_checksum == checksum;
}

bool Message::parseHeader(const ByteArray& data)
{

    return m_header.parse(data.data() + HeaderPos, data.size()) > 0;
}

bool Message::parseBody(const ByteArray& data)
{
    ByteArray body;
    int pos = BodyNoPacketPos;

    if (m_header.bodyProps.bits.segment == 1) {
        pos = BodyPacketPos;
    }

    body.assign(data.begin() + pos, data.begin() + pos + m_header.bodyProps.bits.len);

    m_body = MessageBody::MessageBodyFactory::create(MessageIds(m_header.id));

    m_body->parse(body);

    return m_body->isValid();
}

bool Message::validateJson(const Json& data)
{
    nlohmann::json_schema::basic_error_handler err;
    m_validator.validate(data, err);
    return !err;
}

ByteArray Message::packageHeader()
{
    return m_header.package();
}

ByteArray Message::packageBody()
{
    if (m_body != nullptr) {
        return m_body->package();
    }

    return {};
}

void Message::setHeader(const Header& newHeader)
{
    m_header = newHeader;
}

void Message::setBody(std::unique_ptr<MessageBody::MessageBodyBase> newBody)
{
    m_body = std::move(newBody);
}

void Message::setBody(MessageBody::MessageBodyBase* newBody)
{
    m_body.reset(newBody);
}

MessageBody::MessageBodyBase* Message::body() const
{
    return m_body.get();
}

Message::Header Message::header() const
{
    return m_header;
}

bool Message::isValid() const
{
    return m_isValid;
}

bool Message::Header::operator==(const Header& other) const
{
    return id == other.id && bodyProps.value == other.bodyProps.value && phone == other.phone && seq == other.seq
        && pkgEncap.rawData == other.pkgEncap.rawData;
}

int Message::Header::parse(const uint8_t* data, int size)
{
    int pos = 0;

    if (size >= MinimumMsgSize) {
        // Message ID
        id = MessageIds(Utils::endianSwap16(data));
        pos += sizeof(id);
        // bodyProps
        bodyProps.value = Utils::endianSwap16(data + pos);
        pos += sizeof(bodyProps);
        // phone
        phone = BCD::toString(data + pos, 6);
        pos += 6;
        // seq
        seq = Utils::endianSwap16(data + pos);
        pos += sizeof(seq);

        if (bodyProps.bits.segment == 1 && size - MinimumMsgSize - bodyProps.bits.len == 4) {
            pkgEncap.data.fragTotal = Utils::endianSwap32(data + pos);
            pos += sizeof(pkgEncap.data.fragTotal);
            pkgEncap.data.fragSN = Utils::endianSwap32(data + pos);
            pos += sizeof(pkgEncap.data.fragSN);
        }
    }

    return pos;
}

ByteArray Message::Header::package() const
{
    ByteArray result;

    // id
    Utils::appendU16(id, result);
    // BodyProperties
    Utils::appendU16(bodyProps.value, result);
    // Phone
    Utils::appendBCD(phone, result);
    // sn
    Utils::appendU16(seq, result);
    // Packet encap
    if (bodyProps.bits.segment == 1 && pkgEncap.data.fragTotal > 1) {
        // total Packets
        Utils::appendU16(pkgEncap.data.fragTotal, result);
        // packet sn
        Utils::appendU16(pkgEncap.data.fragSN, result);
    }

    return result;
}

void Message::Header::fromJson(const Json& data)
{
    id = data["id"];
    bodyProps.bits.encrypt = data["encrypt"];
    bodyProps.bits.len = data["length"];
    bodyProps.bits.segment = data.value("segment", 0);
    if (bodyProps.bits.segment) {
        pkgEncap.data.fragTotal = data.value("frag_total", 0);
        pkgEncap.data.fragSN = data.value("frag_seq", 0);
    }

    phone = data["phone"];
    seq = data["seq"];
}

Json Message::Header::toJson()
{
    Json result = Json::object({
        {"id", id},
        {"encrypt", (int)bodyProps.bits.encrypt},
        {"length", (int)bodyProps.bits.len},
        {"segment", (int)bodyProps.bits.segment},
        {"phone", phone},
        {"seq", seq},
    });

    if (bodyProps.bits.segment == 1) {
        result["frag_total"] = pkgEncap.data.fragTotal;
        result["frag_seq"] = pkgEncap.data.fragSN;
    }

    return result;
}

}
