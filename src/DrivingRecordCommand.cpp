#include "JT808/MessageBody/DrivingRecordCommand.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/DrivingRecordCommandSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

DrivingRecordCommand::DrivingRecordCommand()
    : MessageBodyBase(Schema::DrivingRecordCommandSchema)
{
}

DrivingRecordCommand::DrivingRecordCommand(uint8_t command, const std::vector<uint8_t>& param)
    : MessageBodyBase(Schema::DrivingRecordCommandSchema)
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
    // command
    m_command = data[pos++];
    // param
    if (pos < size) {
        m_param.assign(data + pos, data + size);
    }

    setIsValid(true);
}

std::vector<uint8_t> DrivingRecordCommand::package()
{
    std::vector<uint8_t> result;
    // command
    result.push_back(m_command);
    // param
    if (!m_param.empty()) {
        Utils::append(m_param, result);
    }

    return result;
}

bool DrivingRecordCommand::operator==(const DrivingRecordCommand& other) const
{
    return m_command == other.m_command && m_param == other.m_param;
}

void DrivingRecordCommand::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_command = data["command"];
        m_param = data["param"].get<std::vector<uint8_t>>();
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json DrivingRecordCommand::toJson()
{
    return {{"command", m_command}, {"param", m_param}};
}

uint8_t DrivingRecordCommand::command() const
{
    return m_command;
}

void DrivingRecordCommand::setCommand(uint8_t newCommand)
{
    m_command = newCommand;
}

std::vector<uint8_t> DrivingRecordCommand::param() const
{
    return m_param;
}

void DrivingRecordCommand::setParam(const std::vector<uint8_t>& newParam)
{
    m_param = newParam;
}
}
