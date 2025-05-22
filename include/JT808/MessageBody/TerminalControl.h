#ifndef TERMINALCONTROL_H
#define TERMINALCONTROL_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

/**
 * @brief The TerminalControl class
 */
class TerminalControl : public MessageBodyBase
{
public:
    /**
     * @brief Commands
     */
    enum Commands
    {
        WirelessUpgrade = 1,
        ServerConnect = 2,
        TerminalPowerOff = 3,
        TerminalReset = 4,
        TerminalFactoryReset = 5,
        DataCommunicationOff = 6,
        WirelessCommunicationOff = 7
    };

    /**
     * @brief ConnectionControlFlags
     */
    enum ConnectionControlFlags
    {
        SpecificPlatformServer = 0,
        DefaultPlatformServer = 1
    };

    TerminalControl() = default;
    TerminalControl(Commands command, const std::string& param = "");
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalControl& other);

    Commands command() const;
    void setCommand(Commands newCommand);

    std::string param() const;
    void setParam(const std::string& newParam);

    ConnectionControlFlags connectionControl() const;
    void setConnectionControl(ConnectionControlFlags newConnectionControl);
    std::string serverAPN() const;
    void setServerAPN(const std::string& newServerAPN);
    std::string username() const;
    void setUsername(const std::string& newUsername);
    std::string password() const;
    void setPassword(const std::string& newPassword);
    std::string serverAddress() const;
    void setServerAddress(const std::string& newServerAddress);
    uint16_t tcpPort() const;
    void setTcpPort(uint16_t newTcpPort);
    uint16_t udpPort() const;
    void setUdpPort(uint16_t newUdpPort);
    std::vector<uint8_t> manufacturer() const;
    void setManufacturer(const std::vector<uint8_t>& newManufacturer);
    std::string authCode() const;
    void setAuthCode(const std::string& newAuthCode);
    std::string hwVersion() const;
    void setHwVersion(const std::string& newHwVersion);
    std::string fwVersion() const;
    void setFwVersion(const std::string& newFwVersion);
    std::string url() const;
    void setUrl(const std::string& newUrl);
    uint16_t connectionTimeout() const;
    void setConnectionTimeout(uint16_t newConnectionTimeout);

private:
    Commands m_command;
    std::string m_param;

    ConnectionControlFlags m_connectionControl = SpecificPlatformServer;
    std::string m_serverAPN;
    std::string m_username;
    std::string m_password;
    std::string m_serverAddress;
    uint16_t m_tcpPort = 0;
    uint16_t m_udpPort = 0;
    std::vector<uint8_t> m_manufacturer;
    std::string m_authCode;
    std::string m_hwVersion;
    std::string m_fwVersion;
    std::string m_url;
    uint16_t m_connectionTimeout = 0;
};

}

#endif // TERMINALCONTROL_H
