#ifndef TERMINALCONTROL_H
#define TERMINALCONTROL_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

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
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalControl& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

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
