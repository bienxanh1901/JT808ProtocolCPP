#include "JT808/MessageBody/DrivingRecordDataUpload.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

DrivingRecordDataUpload::DrivingRecordDataUpload(uint16_t seq, uint8_t command, const std::string& param)
    : DrivingRecordCommand(command, param)
    , m_seq(seq)
{
}

void DrivingRecordDataUpload::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void DrivingRecordDataUpload::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);

    DrivingRecordCommand::parse(data + pos, size - pos);

    setIsValid(true);
}

std::vector<uint8_t> DrivingRecordDataUpload::package()
{
    std::vector<uint8_t> commandResult(DrivingRecordCommand::package());
    std::vector<uint8_t> result;

    Utils::appendU16(m_seq, result);
    result.insert(result.end(), commandResult.begin(), commandResult.end());
    return result;
}

bool DrivingRecordDataUpload::operator==(const DrivingRecordDataUpload& other)
{
    return DrivingRecordCommand::operator==(other) && m_seq == other.m_seq;
}

uint16_t DrivingRecordDataUpload::seq() const
{
    return m_seq;
}

void DrivingRecordDataUpload::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

}
