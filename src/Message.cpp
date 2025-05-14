#include "JT808/Message.h"
#include "JT808/BCD.h"
#include "JT808/MessageIds.h"
#include "JT808/Utils.h"

#include "JT808/MessageBody/GeneralResponse.h"
#include "JT808/MessageBody/LocationInformationQueryResponse.h"
#include "JT808/MessageBody/LocationInformationReport.h"
#include "JT808/MessageBody/ManualAlarmConfirmation.h"
#include "JT808/MessageBody/SubPackageRetransmissionRequest.h"
#include "JT808/MessageBody/TemporaryLocationTrackingControl.h"
#include "JT808/MessageBody/TerminalAuthentication.h"
#include "JT808/MessageBody/TerminalControl.h"
#include "JT808/MessageBody/TerminalParameterQuery.h"
#include "JT808/MessageBody/TerminalParameterQueryResponse.h"
#include "JT808/MessageBody/TerminalParameterSetting.h"
#include "JT808/MessageBody/TerminalPropertiesQueryResponse.h"
#include "JT808/MessageBody/TerminalRegistration.h"
#include "JT808/MessageBody/TerminalRegistrationResponse.h"
#include "JT808/MessageBody/TerminalUpgradePackage.h"
#include "JT808/MessageBody/TerminalUpgradePackageResult.h"

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

Message::Message(const std::vector<uint8_t>& data)
    : m_rawData(data)
{
}

void Message::package()
{
    m_rawData.clear();

    // package body
    if (!packageBody()) {
        m_isValid = false;
        return;
    }

    // modify body len in header
    m_header.bodyProps.bits.len = m_body->rawData().size();

    // package header
    packageHeader();

    // insert package body
    m_rawData.insert(m_rawData.end(), m_body->rawData().begin(), m_body->rawData().end());

    // checksum
    calculateChecksum(m_rawData.data() + MSG_HEADER_POS, m_rawData.size() - 1);
    m_rawData.push_back(m_checksum);

    // protocol sign
    m_rawData.push_back(ProtocolSign);

    // escape
    escape();
}

void Message::parse()
{
    std::vector<uint8_t> output = reverseEscape(m_rawData);
    calculateChecksum(output.data() + MSG_HEADER_POS, output.size() - 3);
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
}

std::vector<uint8_t> Message::reverseEscape(const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> result;

    for (int i = 0; i < data.size(); i++) {
        if (data[i] == ProtocolEscape && data[i + 1] == ProtocolEscapeSign) {
            result.push_back(ProtocolSign);
            ++i;
        } else if (data[i] == ProtocolEscape && data[i + 1] == ProtocolEscapeEscape) {
            result.push_back(ProtocolEscape);
            ++i;
        } else {
            result.push_back(data[i]);
        }
    }

    return result;
}

void Message::calculateChecksum(uint8_t* data, int len)
{
    m_checksum = 0;

    for (int i = 0; i < len; i++) {
        m_checksum = m_checksum ^ data[i];
    }
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

    std::vector<uint8_t> phone(data.begin() + PHONE_POS, data.begin() + PHONE_POS + PHONE_SIZE);
    m_header.phone = BCD::toString(phone);

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

    setBody(MessageIds(m_header.msgID), body);

    return m_body->isValid();
}

bool Message::packageHeader()
{
    Utils::U16Array u16Data = {0};

    // begin flag
    m_rawData.push_back(ProtocolSign);
    // id
    u16Data.value = Utils::endianSwap16(m_header.msgID);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));
    // BodyProperties
    u16Data.value = Utils::endianSwap16(m_header.bodyProps.value);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));
    // Phone
    std::vector<uint8_t> phone = BCD::fromString(m_header.phone);
    m_rawData.insert(m_rawData.end(), phone.begin(), phone.end());
    // sn
    u16Data.value = Utils::endianSwap16(m_header.msgSN);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));
    // Packet encap
    if (m_header.bodyProps.bits.segment == 1 && m_header.pkgEncap.data.fragTotal > 1) {
        // total Packets
        u16Data.value = Utils::endianSwap16(m_header.pkgEncap.data.fragTotal);
        m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));
        // packet sn
        u16Data.value = Utils::endianSwap16(m_header.pkgEncap.data.fragSN);
        m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));
    }

    return true;
}

bool Message::packageBody()
{
    if (m_body) {
        m_body->package();

        return m_body->isValid();
    }

    return false;
}

void Message::setHeader(const Header& newHeader)
{
    m_header = newHeader;
}

void Message::setBody(std::unique_ptr<MessageBody::MessageBodyBase> newBody)
{
    m_body = std::move(newBody);
}

void Message::setBody(MessageIds id, const std::vector<uint8_t>& rawBodyData)
{

    m_header.msgID = id;

    switch (m_header.msgID) {
    case TerminalGeneralResponse:
    case PlatformGeneralResponse:
        m_body.reset(new MessageBody::GeneralResponse(rawBodyData));
        break;
    case TerminalRegistration:
        m_body.reset(new MessageBody::TerminalRegistration(rawBodyData));
    case TerminalAuthentication:
        m_body.reset(new MessageBody::TerminalAuthentication(rawBodyData));
    case TerminalParameterQueryResponse:
        m_body.reset(new MessageBody::TerminalParameterQueryResponse(rawBodyData));
    case TerminalPropertiesQueryResponse:
        m_body.reset(new MessageBody::TerminalPropertiesQueryResponse(rawBodyData));
    case TerminalUpgradePackageResult:
        m_body.reset(new MessageBody::TerminalUpgradePackageResult(rawBodyData));
    case LocationInformationReport:
        m_body.reset(new MessageBody::LocationInformationReport(rawBodyData));
    case LocationInformationQueryResponse:
        m_body.reset(new MessageBody::LocationInformationQueryResponse(rawBodyData));
    case SubPackageRetransmissionRequest:
        m_body.reset(new MessageBody::SubPackageRetransmissionRequest(rawBodyData));
    case TerminalRegistrationResponse:
        m_body.reset(new MessageBody::TerminalRegistrationResponse(rawBodyData));
    case TerminalParameterSetting:
        m_body.reset(new MessageBody::TerminalParameterSetting(rawBodyData));
    case TerminalControl:
        m_body.reset(new MessageBody::TerminalControl(rawBodyData));
    case TerminalSpecificParameterQuery:
        m_body.reset(new MessageBody::TerminalParameterQuery(rawBodyData));
    case TerminalUpgradePackage:
        m_body.reset(new MessageBody::TerminalUpgradePackage(rawBodyData));
    case TemporaryLocationTrackingControl:
        m_body.reset(new MessageBody::TemporaryLocationTrackingControl(rawBodyData));
    case ManualAlarmConfirmation:
        m_body.reset(new MessageBody::ManualAlarmConfirmation(rawBodyData));
    case TerminalHeartBeat:
    case TerminalParameterQuery:
    case TerminalLogout:
    case TerminalPropertiesQuery:
    case LocationInformationQuery:
    default:
        m_body.reset(new MessageBody::MessageBodyBase(rawBodyData));
    }

    m_body->parse();
}

void Message::setBody(MessageBody::MessageBodyBase* newBody)
{
    m_body.reset(newBody);
}

void Message::setId(MessageIds id)
{
    m_header.msgID = id;
}

MessageIds Message::id()
{
    return MessageIds(m_header.msgID);
}

std::vector<uint8_t> Message::rawData() const
{
    return m_rawData;
}

void Message::setRawData(const std::vector<uint8_t>& newRawData)
{
    m_rawData = newRawData;
}

void Message::escape()
{
    std::vector<uint8_t> result;

    m_rawData[0] = 0x00;
    m_rawData[m_rawData.size() - 1] = 0x00;

    for (auto& val : m_rawData) {
        if (val == ProtocolSign) {
            result.push_back(ProtocolEscape);
            result.push_back(ProtocolEscapeSign);
        } else if (val == ProtocolEscape) {
            result.push_back(ProtocolEscape);
            result.push_back(ProtocolEscapeEscape);
        } else {
            result.push_back(val);
        }
    }

    m_rawData = result;
    m_rawData[0] = ProtocolSign;
    m_rawData[m_rawData.size() - 1] = ProtocolSign;
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
