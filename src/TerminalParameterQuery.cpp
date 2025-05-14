#include "JT808/MessageBody/TerminalParameterQuery.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

TerminalParameterQuery::TerminalParameterQuery(const std::vector<uint32_t>& ids)
    : MessageBodyBase()
    , m_length(ids.size())
    , m_ids(ids)
{
}

void TerminalParameterQuery::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalParameterQuery::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_length = data[pos++];

    if (m_length * 4 != size - pos) {
        setIsValid(false);
        return;
    }

    uint32_t id = 0;
    for (int i = 0; i < m_length; i++) {
        id = Utils::endianSwap32(data + pos);
        pos += sizeof(id);
        m_ids.push_back(id);
    }

    setIsValid(true);
}

std::vector<uint8_t> TerminalParameterQuery::package()
{
    std::vector<uint8_t> result;
    result.push_back(m_length);

    for (const auto& id : m_ids) {
        Utils::appendU32(id, result);
    }

    return result;
}

bool TerminalParameterQuery::operator==(const TerminalParameterQuery& other)
{
    return m_length == other.m_length && m_ids == other.m_ids;
}

uint8_t TerminalParameterQuery::length() const
{
    return m_length;
}

void TerminalParameterQuery::setLength(uint8_t newLength)
{
    m_length = newLength;
}

std::vector<uint32_t> TerminalParameterQuery::ids() const
{
    return m_ids;
}

void TerminalParameterQuery::setIds(const std::vector<uint32_t>& newIds)
{
    m_ids = newIds;
}

}
