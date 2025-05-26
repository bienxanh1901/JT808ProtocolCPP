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

        m_param = Utils::gbkDecode(data + pos, size - pos);
    }

    setIsValid(true);
}

std::vector<uint8_t> TerminalControl::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_command);
    if (m_command <= ServerConnect) {
        Utils::appendGBK(m_param, result);
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

}
