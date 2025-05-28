#include "JT808/MessageBody/TerminalControl.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

TerminalControl::TerminalControl(Commands command, std::string param)
    : m_command(command)
    , m_param(std::move(param))
{
}

void TerminalControl::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalControl::parse(const uint8_t* data, int size)
{
    int pos = 0;

    // command
    m_command = Commands(data[pos++]);
    // param
    if (m_command <= ServerConnect) {
        m_param = Utils::gbkDecode(data + pos, size - pos);
    }

    setIsValid(true);
}

std::vector<uint8_t> TerminalControl::package()
{
    std::vector<uint8_t> result;

    // command
    result.push_back(m_command);
    if (m_command <= ServerConnect) {
        // param
        Utils::appendGBK(m_param, result);
    }

    return result;
}

bool TerminalControl::operator==(const TerminalControl& other) const
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

}
