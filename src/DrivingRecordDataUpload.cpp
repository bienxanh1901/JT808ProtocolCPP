#include "JT808/MessageBody/DrivingRecordDataUpload.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/DrivingRecordDataUploadSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

DrivingRecordDataUpload::DrivingRecordDataUpload()
    : MessageBodyBase(Schema::DrivingRecordDataUploadSchema)
{
}

DrivingRecordDataUpload::DrivingRecordDataUpload(uint16_t seq, uint8_t command, const std::vector<uint8_t>& data)
    : MessageBodyBase(Schema::DrivingRecordDataUploadSchema)
    , m_seq(seq)
    , m_command(command)
    , m_data(data)
{
}

void DrivingRecordDataUpload::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void DrivingRecordDataUpload::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // seq
    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
    // command
    m_command = data[pos++];
    // data
    m_data.assign(data + pos, data + size);

    setIsValid(true);
}

std::vector<uint8_t> DrivingRecordDataUpload::package()
{
    std::vector<uint8_t> result;
    // seq
    Utils::appendU16(m_seq, result);
    // command
    result.push_back(m_command);
    // data
    Utils::append(m_data, result);
    return result;
}

bool DrivingRecordDataUpload::operator==(const DrivingRecordDataUpload& other) const
{
    return m_seq == other.m_seq && m_command == other.m_command && m_data == other.m_data;
}

void DrivingRecordDataUpload::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        m_command = data["command"];
        m_data = data["data"].get<std::vector<uint8_t>>();
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json DrivingRecordDataUpload::toJson()
{
    return {{"seq", m_seq}, {"command", m_command}, {"data", m_data}};
}

uint16_t DrivingRecordDataUpload::seq() const
{
    return m_seq;
}

void DrivingRecordDataUpload::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

uint8_t DrivingRecordDataUpload::command() const
{
    return m_command;
}

void DrivingRecordDataUpload::setCommand(uint8_t newCommand)
{
    m_command = newCommand;
}

std::vector<uint8_t> DrivingRecordDataUpload::data() const
{
    return m_data;
}

void DrivingRecordDataUpload::setData(const std::vector<uint8_t>& newData)
{
    m_data = newData;
}

}
