#include "JT808/MessageBody/QuestionResponse.h"
#include "JT808/MessageBody/SequenceMessageBodyBase.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

QuestionResponse::QuestionResponse(uint16_t seq, uint8_t id)
    : SequenceMessageBodyBase(seq)
    , m_id(id)
{
}

void QuestionResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void QuestionResponse::parse(const uint8_t* data, int size)
{
    SequenceMessageBodyBase::parse(data, size);

    m_id = data[2];

    setIsValid(true);
}

std::vector<uint8_t> QuestionResponse::package()
{
    std::vector<uint8_t> result(SequenceMessageBodyBase::package());

    result.push_back(m_id);

    return result;
}

bool QuestionResponse::operator==(const QuestionResponse& other) const
{
    return SequenceMessageBodyBase::operator==(other) && m_id == other.m_id;
}

uint8_t QuestionResponse::id() const
{
    return m_id;
}

void QuestionResponse::setId(uint8_t newId)
{
    m_id = newId;
}

}
