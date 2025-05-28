#include "JT808/MessageBody/SequenceMessageBodyBase.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

SequenceMessageBodyBase::SequenceMessageBodyBase(uint16_t seq)
    : m_seq(seq)
{
}

void SequenceMessageBodyBase::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void SequenceMessageBodyBase::parse(const uint8_t* data, int size)
{
    if (size < 2) {
        setIsValid(false);
        return;
    }

    m_seq = Utils::endianSwap16(data);
}

std::vector<uint8_t> SequenceMessageBodyBase::package()
{
    std::vector<uint8_t> result;

    Utils::appendU16(m_seq, result);

    return result;
}

bool SequenceMessageBodyBase::operator==(const SequenceMessageBodyBase& other) const
{
    return m_seq == other.m_seq;
}

uint16_t SequenceMessageBodyBase::seq() const
{
    return m_seq;
}

void SequenceMessageBodyBase::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

}
