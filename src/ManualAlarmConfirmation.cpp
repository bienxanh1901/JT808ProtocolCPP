#include "JT808/MessageBody/ManualAlarmConfirmation.h"
#include "JT808/MessageBody/SequenceMessageBodyBase.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {
ManualAlarmConfirmation::ManualAlarmConfirmation(uint16_t seq, ManualAlarmConfirmationTypes type)
    : SequenceMessageBodyBase(seq)
    , m_type(type)
{
}

void ManualAlarmConfirmation::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void ManualAlarmConfirmation::parse(const uint8_t* data, int size)
{
    // seq
    SequenceMessageBodyBase::parse(data, size);
    // type
    m_type.value = Utils::endianSwap32(data + 2);
    setIsValid(true);
}

std::vector<uint8_t> ManualAlarmConfirmation::package()
{
    // seq
    std::vector<uint8_t> result(SequenceMessageBodyBase::package());
    // type
    Utils::appendU32(m_type.value, result);

    return result;
}

bool ManualAlarmConfirmation::operator==(const ManualAlarmConfirmation& other) const
{
    return SequenceMessageBodyBase::operator==(other) && m_type.value == other.m_type.value;
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
