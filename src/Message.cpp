#include "JT808/Message.h"
#include "JT808/BCD.h"
#include "JT808/MessageBody/MessageBodyFactory.h"
#include "JT808/MessageIds.h"
#include "JT808/Utils.h"

#define MINIMUM_MSG_SIZE 15
#define MSG_HEADER_POS 1
#define MSG_ID_POS 1
#define MSG_ID_SIZE 2
#define BODY_PROPS_POS MSG_ID_POS + MSG_ID_SIZE
#define BODY_PROPS_SIZE 2
#define PHONE_POS BODY_PROPS_POS + BODY_PROPS_SIZE
#define PHONE_SIZE 6
#define MSG_SN_POS PHONE_POS + PHONE_SIZE
#define MSG_SN_SIZE 2
#define PKG_ENCAP_POS MSG_SN_POS + MSG_SN_SIZE
#define PKG_ENCAP_SIZE 4

#define MSG_BODY_NO_PACKET_POS PKG_ENCAP_POS
#define MSG_BODY_PACKET_POS PKG_ENCAP_POS + PKG_ENCAP_SIZE

namespace JT808 {

Message::Message() { }

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
    // package header
    std::vector<uint8_t> headerRawData(packageHeader());
    // insert header
    result.insert(result.end(), headerRawData.begin(), headerRawData.end());
    // insert body
    result.insert(result.end(), bodyRawData.begin(), bodyRawData.end());
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
    m_checksum = Utils::calculateChecksum(output.data() + MSG_HEADER_POS, output.size() - 3);
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
    if (data.size() < MINIMUM_MSG_SIZE)
        return false;

    // Message ID
    m_header.msgID = data[MSG_ID_POS] * 256 + data[MSG_ID_POS + MSG_ID_SIZE - 1];
    m_header.bodyProps.value = data[BODY_PROPS_POS] * 256 + data[BODY_PROPS_POS + BODY_PROPS_SIZE - 1];
    m_header.phone = BCD::toString(data.data() + PHONE_POS, PHONE_SIZE);
    m_header.msgSN = data[MSG_SN_POS] * 256 + data[MSG_SN_POS + MSG_SN_SIZE - 1];

    if (m_header.bodyProps.bits.segment == 1 && data.size() - MINIMUM_MSG_SIZE - m_header.bodyProps.bits.len == 4) {
        m_header.pkgEncap.data.fragSN = data[PKG_ENCAP_POS] * 256 + data[PKG_ENCAP_POS + 1];
        m_header.pkgEncap.data.fragTotal = data[PKG_ENCAP_POS + 2] * 256 + data[PKG_ENCAP_POS + PKG_ENCAP_SIZE - 1];
    }

    return true;
}

bool Message::parseBody(const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> body;
    int pos = MSG_BODY_NO_PACKET_POS;

    if (m_header.bodyProps.bits.segment == 1) {
        pos = MSG_BODY_NO_PACKET_POS;
    }

    body.assign(data.begin() + pos, data.begin() + pos + m_header.bodyProps.bits.len);

    m_body = MessageBody::MessageBodyFactory::create(MessageIds(m_header.msgID));

    m_body->parse(body);

    return m_body->isValid();
}

std::vector<uint8_t> Message::packageHeader()
{
    std::vector<uint8_t> result;

    // id
    Utils::appendU16(m_header.msgID, result);
    // BodyProperties
    Utils::appendU16(m_header.bodyProps.value, result);
    // Phone
    Utils::appendBCD(m_header.phone, result);
    // sn
    Utils::appendU16(m_header.msgSN, result);
    // Packet encap
    if (m_header.bodyProps.bits.segment == 1 && m_header.pkgEncap.data.fragTotal > 1) {
        // total Packets
        Utils::appendU16(m_header.pkgEncap.data.fragTotal, result);
        // packet sn
        Utils::appendU16(m_header.pkgEncap.data.fragSN, result);
    }

    return result;
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

}
