#include "JT808/MessageBody/ManualAlarmConfirmation.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/ManualAlarmConfirmationSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {
ManualAlarmConfirmation::ManualAlarmConfirmation()
    : MessageBodyBase(Schema::ManualAlarmConfirmationSchema)
{
}

ManualAlarmConfirmation::ManualAlarmConfirmation(uint16_t seq, ManualAlarmConfirmationTypes type)
    : MessageBodyBase(Schema::ManualAlarmConfirmationSchema)
    , m_seq(seq)
    , m_type(type)
{
}

void ManualAlarmConfirmation::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void ManualAlarmConfirmation::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    // seq
    m_seq = Utils::endianSwap16(data);
    pos += sizeof(m_seq);
    // type
    m_type.value = Utils::endianSwap32(data + pos);
    setIsValid(true);
}

std::vector<uint8_t> ManualAlarmConfirmation::package()
{
    std::vector<uint8_t> result;
    // seq
    Utils::appendU16(m_seq, result);
    // type
    Utils::appendU32(m_type.value, result);

    return result;
}

bool ManualAlarmConfirmation::operator==(const ManualAlarmConfirmation& other) const
{
    return m_seq == other.m_seq && m_type.value == other.m_type.value;
}

void ManualAlarmConfirmation::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        m_type.value = data["type"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json ManualAlarmConfirmation::toJson()
{
    return {{"seq", m_seq}, {"type", m_type.value}};
}

ManualAlarmConfirmationTypes ManualAlarmConfirmation::type() const
{
    return m_type;
}

void ManualAlarmConfirmation::setType(const ManualAlarmConfirmationTypes& newType)
{
    m_type = newType;
}

uint16_t ManualAlarmConfirmation::seq() const
{
    return m_seq;
}

void ManualAlarmConfirmation::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

}
