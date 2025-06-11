#include "JT808/MessageBody/TerminalControl.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/TerminalControlSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>

namespace JT808::MessageBody {

TerminalControl::TerminalControl()
    : MessageBodyBase(Schema::TerminalControlSchema)
{
}

TerminalControl::TerminalControl(Commands command, std::string param)
    : MessageBodyBase(Schema::TerminalControlSchema)
    , m_command(command)
    , m_param(std::move(param))
{
}

void TerminalControl::parse(const ByteArray& data)
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

ByteArray TerminalControl::package()
{
    ByteArray result;

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

void TerminalControl::fromJson(const Json& data)
{
    if (validate(data)) {
        m_command = data["command"];
        m_param = data.value("param", "");
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json TerminalControl::toJson()
{
    Json result({{"command", m_command}});
    if (m_command <= ServerConnect) {
        result["param"] = m_param;
    }
    return result;
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
