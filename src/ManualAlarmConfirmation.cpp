#include "JT808/MessageBody/ManualAlarmConfirmation.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {
ManualAlarmConfirmation::ManualAlarmConfirmation(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

ManualAlarmConfirmation::ManualAlarmConfirmation(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void ManualAlarmConfirmation::parse()
{
    uint8_t* data = m_rawData.data();
    int pos = 0;

    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
    m_type.value = Utils::endianSwap32(data + pos);
    m_isValid = true;
}

void ManualAlarmConfirmation::package()
{
    Utils::U16Array u16Data = {0};
    Utils::U32Array u32Data = {0};

    m_rawData.clear();

    u16Data.value = Utils::endianSwap16(m_seq);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    u32Data.value = Utils::endianSwap32(m_type.value);
    m_rawData.insert(m_rawData.end(), u32Data.array, u32Data.array + sizeof(u32Data));

    m_isValid = true;
}

uint16_t ManualAlarmConfirmation::seq() const
{
    return m_seq;
}

void ManualAlarmConfirmation::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

ManualAlarmConfirmationTypes ManualAlarmConfirmation::type() const
{
    return m_type;
}

void ManualAlarmConfirmation::setType(const ManualAlarmConfirmationTypes& newType)
{
    m_type = newType;
}

}
}
