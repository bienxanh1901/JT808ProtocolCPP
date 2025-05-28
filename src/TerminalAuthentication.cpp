#include "JT808/MessageBody/TerminalAuthentication.h"

namespace JT808::MessageBody {

TerminalAuthentication::TerminalAuthentication(const std::string authCode)
    : MessageBodyBase()
    , m_authCode(authCode)
{
}

void TerminalAuthentication::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalAuthentication::parse(const uint8_t* data, int size)
{
    m_authCode.assign(data, data + size);
    setIsValid(true);
}

std::vector<uint8_t> TerminalAuthentication::package()
{
    std::vector<uint8_t> result(m_authCode.begin(), m_authCode.end());

    return result;
}

bool TerminalAuthentication::operator==(const TerminalAuthentication& other) const
{
    return m_authCode == other.m_authCode;
}

std::string TerminalAuthentication::authCode() const
{
    return m_authCode;
}

void TerminalAuthentication::setAuthCode(const std::string& newAuthCode)
{
    m_authCode = newAuthCode;
}

}
