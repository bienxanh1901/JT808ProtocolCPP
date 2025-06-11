#ifndef TERMINALCONTROL_H
#define TERMINALCONTROL_H

#include "JT808/Common.h"
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
    enum Commands : uint8_t
    {
        WirelessUpgrade = 1,
        ServerConnect = 2,
        TerminalPowerOff = 3,
        TerminalReset = 4,
        TerminalFactoryReset = 5,
        DataCommunicationOff = 6,
        WirelessCommunicationOff = 7
    };

    TerminalControl();
    TerminalControl(Commands command, std::string param = "");
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalControl& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    Commands command() const;
    void setCommand(Commands newCommand);
    std::string param() const;
    void setParam(const std::string& newParam);

private:
    Commands m_command = WirelessUpgrade;
    std::string m_param;
};

}

#endif // TERMINALCONTROL_H
