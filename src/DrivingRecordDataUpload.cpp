#include "JT808/MessageBody/DrivingRecordDataUpload.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/DrivingRecordDataUploadSchema.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

DrivingRecordDataUpload::DrivingRecordDataUpload()
    : MessageBodyBase(Schema::DrivingRecordDataUploadSchema)
{
}

DrivingRecordDataUpload::DrivingRecordDataUpload(uint16_t seq, uint8_t command, const ByteArray& data)
    : MessageBodyBase(Schema::DrivingRecordDataUploadSchema)
    , m_seq(seq)
    , m_command(command)
    , m_data(data)
{
}

void DrivingRecordDataUpload::parse(const ByteArray& data)
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

ByteArray DrivingRecordDataUpload::package()
{
    ByteArray result;
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

void DrivingRecordDataUpload::fromJson(const Json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        m_command = data["command"];
        m_data = data["data"].get<ByteArray>();
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json DrivingRecordDataUpload::toJson()
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

ByteArray DrivingRecordDataUpload::data() const
{
    return m_data;
}

void DrivingRecordDataUpload::setData(const ByteArray& newData)
{
    m_data = newData;
}

}
