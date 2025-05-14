#include "JT808/MessageBody/TerminalAuthentication.h"

namespace JT808 {
namespace MessageBody {

TerminalAuthentication::TerminalAuthentication(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

TerminalAuthentication::TerminalAuthentication(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void TerminalAuthentication::parse()
{
    m_isValid = true;
    m_authCode.assign(m_rawData.begin(), m_rawData.end());
}

void TerminalAuthentication::package()
{
    m_rawData.clear();
    m_rawData.assign(m_authCode.begin(), m_authCode.end());

    m_isValid = true;
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
}
