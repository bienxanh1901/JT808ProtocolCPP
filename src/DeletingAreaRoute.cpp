#include "JT808/MessageBody/DeletingAreaRoute.h"

namespace JT808::MessageBody {

DeletingAreaRoute::DeletingAreaRoute(const std::vector<uint16_t>& ids)
    : MessageBodyBase()
    , m_length(ids.size())
    , m_ids(ids)
{
}

void DeletingAreaRoute::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void DeletingAreaRoute::parse(const uint8_t* data, int size)
{
    int pos = 0;
    m_length = data[pos++];

    for (int i = 0; i < m_length; i++) {
        m_ids.push_back(Utils::endianSwap32(data + pos));
        pos += 4;
    }

    setIsValid(true);
}

std::vector<uint8_t> DeletingAreaRoute::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_length);

    for (auto& id : m_ids) {
        Utils::appendU32(id, result);
    }

    return result;
}

bool DeletingAreaRoute::operator==(const DeletingAreaRoute& other)
{
    return m_length == other.m_length && m_ids == other.m_ids;
}

uint8_t DeletingAreaRoute::length() const
{
    return m_length;
}

void DeletingAreaRoute::setLength(uint8_t newLength)
{
    m_length = newLength;
}

std::vector<uint16_t> DeletingAreaRoute::ids() const
{
    return m_ids;
}

void DeletingAreaRoute::setIds(const std::vector<uint16_t>& newIds)
{
    m_ids = newIds;
}
}
