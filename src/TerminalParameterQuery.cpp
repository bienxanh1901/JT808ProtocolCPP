#include "JT808/MessageBody/TerminalParameterQuery.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {

TerminalParameterQuery::TerminalParameterQuery(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

TerminalParameterQuery::TerminalParameterQuery(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void TerminalParameterQuery::parse()
{
    uint8_t* data = m_rawData.data();
    int pos = 0;

    m_length = data[pos++];

    uint32_t id = 0;

    for (int i = 0; i < m_length; i++) {
        id = Utils::endianSwap32(data + pos);
        pos += sizeof(id);
        m_ids.push_back(id);
    }

    m_isValid = true;
}

void TerminalParameterQuery::package()
{
    Utils::U32Array u32Data = {0};

    m_rawData.clear();
    m_rawData.push_back(m_length);

    for (const auto& id : m_ids) {
        u32Data.value = Utils::endianSwap32(id);
        m_rawData.insert(m_rawData.end(), u32Data.array, u32Data.array + sizeof(u32Data));
    }

    m_isValid = true;
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
}
