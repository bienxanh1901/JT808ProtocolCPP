#include "JT808/MessageBody/DrivingRecordCommand.h"

namespace JT808::MessageBody {

DrivingRecordCommand::DrivingRecordCommand(uint8_t command, const std::string& param)
    : MessageBodyBase()
    , m_command(command)
    , m_param(param)
{
}

void DrivingRecordCommand::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void DrivingRecordCommand::parse(const uint8_t* data, int size)
{
    int pos = 0;
    m_command = uint8_t(data[pos++]);
    if (pos < size) {
        m_param.assign(data + pos, data + size);
    }

    setIsValid(true);
}

std::vector<uint8_t> DrivingRecordCommand::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_command);
    if (!m_param.empty()) {
        result.insert(result.end(), m_param.begin(), m_param.end());
    }

    return result;
}

bool DrivingRecordCommand::operator==(const DrivingRecordCommand& other)
{
    return m_command == other.m_command && m_param == other.m_param;
}

uint8_t DrivingRecordCommand::command() const
{
    return m_command;
}

void DrivingRecordCommand::setCommand(uint8_t newCommand)
{
    m_command = newCommand;
}

std::string DrivingRecordCommand::param() const
{
    return m_param;
}

void DrivingRecordCommand::setParam(const std::string& newParam)
{
    m_param = newParam;
}
}
