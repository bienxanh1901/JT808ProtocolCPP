#include "JT808/MessageBody/TerminalRegistrationResponse.h"
#include "JT808/Utils.h"
#include <cstring>

namespace JT808 {
namespace MessageBody {

TerminalRegistrationResponse::TerminalRegistrationResponse(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

TerminalRegistrationResponse::TerminalRegistrationResponse(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void TerminalRegistrationResponse::parse()
{
    uint8_t* data = m_rawData.data();
    int pos = 0;

    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
    m_result = ResponseResults(data[pos++]);

    if (m_result == Succeeded) {
        m_authCode.assign(m_rawData.begin() + pos, m_rawData.end());
    }

    m_isValid = true;
}

void TerminalRegistrationResponse::package()
{
    Utils::U16Array u16Data = {0};

    m_rawData.clear();

    u16Data.value = Utils::endianSwap16(m_seq);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    m_rawData.push_back(m_result);

    if (m_result == Succeeded) {
        m_rawData.insert(m_rawData.end(), m_authCode.begin(), m_authCode.end());
    }

    m_isValid = true;
}

uint16_t TerminalRegistrationResponse::seq() const
{
    return m_seq;
}

void TerminalRegistrationResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

TerminalRegistrationResponse::ResponseResults TerminalRegistrationResponse::result() const
{
    return m_result;
}

void TerminalRegistrationResponse::setResult(ResponseResults newResult)
{
    m_result = newResult;
}

std::string TerminalRegistrationResponse::authCode() const
{
    return m_authCode;
}

void TerminalRegistrationResponse::setAuthCode(const std::string& newAuthCode)
{
    m_authCode = newAuthCode;
}

}
}
