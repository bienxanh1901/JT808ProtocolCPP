#include "JT808/MessageBody/TerminalControl.h"

namespace JT808::MessageBody {

TerminalControl::TerminalControl(Commands command, const std::string& param)
    : MessageBodyBase()
    , m_command(command)
    , m_param(param)
{
}

void TerminalControl::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalControl::parse(const uint8_t* data, int size)
{
    int pos = 0;
    m_command = Commands(data[pos++]);
    if (m_command <= ServerConnect) {
        m_param.assign(data + pos, data + size);
        // TODO convert from GBK to Utf-8, and parse the param
    }

    setIsValid(true);
}

std::vector<uint8_t> TerminalControl::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_command);
    if (m_command <= ServerConnect) {
        result.insert(result.end(), m_param.begin(), m_param.end());
    }

    return result;
}

bool TerminalControl::operator==(const TerminalControl& other)
{
    return m_command == other.m_command && m_param == other.m_param;
}

TerminalControl::Commands TerminalControl::command() const
{
    return m_command;
}

void TerminalControl::setCommand(Commands newCommand)
{
    m_command = newCommand;
}

std::string TerminalControl::param() const
{
    return m_param;
}

void TerminalControl::setParam(const std::string& newParam)
{
    m_param = newParam;
}

TerminalControl::ConnectionControlFlags TerminalControl::connectionControl() const
{
    return m_connectionControl;
}

void TerminalControl::setConnectionControl(ConnectionControlFlags newConnectionControl)
{
    m_connectionControl = newConnectionControl;
}

std::string TerminalControl::serverAPN() const
{
    return m_serverAPN;
}

void TerminalControl::setServerAPN(const std::string& newServerAPN)
{
    m_serverAPN = newServerAPN;
}

std::string TerminalControl::username() const
{
    return m_username;
}

void TerminalControl::setUsername(const std::string& newUsername)
{
    m_username = newUsername;
}

std::string TerminalControl::password() const
{
    return m_password;
}

void TerminalControl::setPassword(const std::string& newPassword)
{
    m_password = newPassword;
}

std::string TerminalControl::serverAddress() const
{
    return m_serverAddress;
}

void TerminalControl::setServerAddress(const std::string& newServerAddress)
{
    m_serverAddress = newServerAddress;
}

uint16_t TerminalControl::tcpPort() const
{
    return m_tcpPort;
}

void TerminalControl::setTcpPort(uint16_t newTcpPort)
{
    m_tcpPort = newTcpPort;
}

uint16_t TerminalControl::udpPort() const
{
    return m_udpPort;
}

void TerminalControl::setUdpPort(uint16_t newUdpPort)
{
    m_udpPort = newUdpPort;
}

std::vector<uint8_t> TerminalControl::manufacturer() const
{
    return m_manufacturer;
}

void TerminalControl::setManufacturer(const std::vector<uint8_t>& newManufacturer)
{
    m_manufacturer = newManufacturer;
}

std::string TerminalControl::authCode() const
{
    return m_authCode;
}

void TerminalControl::setAuthCode(const std::string& newAuthCode)
{
    m_authCode = newAuthCode;
}

std::string TerminalControl::hwVersion() const
{
    return m_hwVersion;
}

void TerminalControl::setHwVersion(const std::string& newHwVersion)
{
    m_hwVersion = newHwVersion;
}

std::string TerminalControl::fwVersion() const
{
    return m_fwVersion;
}

void TerminalControl::setFwVersion(const std::string& newFwVersion)
{
    m_fwVersion = newFwVersion;
}

std::string TerminalControl::url() const
{
    return m_url;
}

void TerminalControl::setUrl(const std::string& newUrl)
{
    m_url = newUrl;
}

uint16_t TerminalControl::connectionTimeout() const
{
    return m_connectionTimeout;
}

void TerminalControl::setConnectionTimeout(uint16_t newConnectionTimeout)
{
    m_connectionTimeout = newConnectionTimeout;
}
}
