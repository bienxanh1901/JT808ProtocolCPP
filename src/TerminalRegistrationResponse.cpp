#include "JT808/MessageBody/TerminalRegistrationResponse.h"

namespace JT808::MessageBody {

TerminalRegistrationResponse::TerminalRegistrationResponse(uint16_t seq, ResponseResults result,
                                                           const std::string& authCode)
    : SequenceMessageBodyBase(seq)
    , m_result(result)
    , m_authCode(authCode)
{
}

void TerminalRegistrationResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalRegistrationResponse::parse(const uint8_t* data, int size)
{
    int pos = 2;
    // seq
    SequenceMessageBodyBase::parse(data, size);
    // result
    m_result = ResponseResults(data[pos++]);
    // authentication code
    if (m_result == Succeeded) {
        m_authCode.assign(data + pos, data + size);
    }

    setIsValid(true);
}

std::vector<uint8_t> TerminalRegistrationResponse::package()
{
    // seq
    std::vector<uint8_t> result(SequenceMessageBodyBase::package());
    // result
    result.push_back(m_result);
    // authentication code
    if (m_result == Succeeded) {
        Utils::append(m_authCode, result);
    }

    return result;
}

bool TerminalRegistrationResponse::operator==(const TerminalRegistrationResponse& other) const
{
    return SequenceMessageBodyBase::operator==(other) && m_result == other.m_result && m_authCode == other.m_authCode;
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
