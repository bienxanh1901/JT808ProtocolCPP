#include "JT808/Message.h"
#include "JT808/BCD.h"
#include "JT808/MessageBody/MessageBodyFactory.h"
#include "JT808/MessageIds.h"
#include "JT808/Utils.h"

namespace JT808 {

enum MessageDef
{
    MinimumMsgSize = 15, // 1 (begin marker) + 12 (header no pkg) + 1 (checksum) + 1 (end marker)
    HeaderPos = 1,
    HeaderNoPacketSize = 12,
    HeaderPacketSize = 16,
    BodyNoPacketPos = HeaderPos + HeaderNoPacketSize,
    BodyPacketPos = HeaderPos + HeaderPacketSize,
};

Message::Message(const Header& header, std::unique_ptr<MessageBody::MessageBodyBase> body)
    : m_header(header)
    , m_body(std::move(body))
{
}

std::vector<uint8_t> Message::package()
{
    std::vector<uint8_t> result;

    // package body
    std::vector<uint8_t> bodyRawData(packageBody());
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

void Message::parse(const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> output = Utils::reverseEscape(data);
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

bool Message::parseHeader(const std::vector<uint8_t>& data)
{

    return m_header.parse(data.data() + HeaderPos, data.size()) > 0;
}

bool Message::parseBody(const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> body;
    int pos = BodyNoPacketPos;

    if (m_header.bodyProps.bits.segment == 1) {
        pos = BodyPacketPos;
    }

    body.assign(data.begin() + pos, data.begin() + pos + m_header.bodyProps.bits.len);

    m_body = MessageBody::MessageBodyFactory::create(MessageIds(m_header.id));

    m_body->parse(body);

    return m_body->isValid();
}

std::vector<uint8_t> Message::packageHeader()
{
    return m_header.package();
}

std::vector<uint8_t> Message::packageBody()
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
        id = Utils::endianSwap16(data);
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

std::vector<uint8_t> Message::Header::package()
{
    std::vector<uint8_t> result;

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

}
