#include "JT808/MessageBody/DeletingCircleArea.h"
#include "JT808/BCD.h"

namespace JT808::MessageBody {

DeletingCircleArea::DeletingCircleArea(const std::vector<uint16_t>& ids)
    : MessageBodyBase()
    , m_length(ids.size())
    , m_ids(ids)
{
}

void DeletingCircleArea::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void DeletingCircleArea::parse(const uint8_t* data, int size)
{
    int pos = 0;
    m_length = data[pos++];

    for (int i = 0; i < m_length; i++) {
        m_ids.push_back(Utils::endianSwap32(data + pos));
        pos += 4;
    }

    setIsValid(true);
}

std::vector<uint8_t> DeletingCircleArea::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_length);

    for (auto& id : m_ids) {
        Utils::appendU32(id, result);
    }

    return result;
}

bool DeletingCircleArea::operator==(const DeletingCircleArea& other)
{
    return m_length == other.m_length && m_ids == other.m_ids;
}

uint8_t DeletingCircleArea::length() const
{
    return m_length;
}

void DeletingCircleArea::setLength(uint8_t newLength)
{
    m_length = newLength;
}

std::vector<uint16_t> DeletingCircleArea::ids() const
{
    return m_ids;
}

void DeletingCircleArea::setIds(const std::vector<uint16_t>& newIds)
{
    m_ids = newIds;
}
}
