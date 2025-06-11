#include "JT808/MessageBody/DrivingRecordCommand.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/DrivingRecordCommandSchema.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

DrivingRecordCommand::DrivingRecordCommand()
    : MessageBodyBase(Schema::DrivingRecordCommandSchema)
{
}

DrivingRecordCommand::DrivingRecordCommand(uint8_t command, const ByteArray& param)
    : MessageBodyBase(Schema::DrivingRecordCommandSchema)
    , m_command(command)
    , m_param(param)
{
}

void DrivingRecordCommand::parse(const ByteArray& data)
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

ByteArray DrivingRecordCommand::package()
{
    ByteArray result;
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

void DrivingRecordCommand::fromJson(const Json& data)
{
    if (validate(data)) {
        m_command = data["command"];
        m_param = data["param"].get<ByteArray>();
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json DrivingRecordCommand::toJson()
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

ByteArray DrivingRecordCommand::param() const
{
    return m_param;
}

void DrivingRecordCommand::setParam(const ByteArray& newParam)
{
    m_param = newParam;
}
}
