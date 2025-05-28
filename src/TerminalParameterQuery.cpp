#include "JT808/MessageBody/TerminalParameterQuery.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

TerminalParameterQuery::TerminalParameterQuery(const std::vector<uint32_t>& ids)
    : m_ids(ids)
{
}

void TerminalParameterQuery::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalParameterQuery::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // length
    uint8_t const length = data[pos++];
    if (length * 4 != size - pos) {
        setIsValid(false);
        return;
    }
    // ids
    uint32_t id = 0;
    for (int i = 0; i < length; i++) {
        id = Utils::endianSwap32(data + pos);
        pos += sizeof(id);
        m_ids.push_back(id);
    }

    setIsValid(true);
}

std::vector<uint8_t> TerminalParameterQuery::package()
{
    std::vector<uint8_t> result;
    // length
    result.push_back(m_ids.size());
    // ids
    Utils::append(m_ids, result);

    return result;
}

bool TerminalParameterQuery::operator==(const TerminalParameterQuery& other) const
{
    return m_ids == other.m_ids;
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
