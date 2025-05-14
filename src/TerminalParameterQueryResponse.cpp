#include "JT808/MessageBody/TerminalParameterQueryResponse.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {

TerminalParameterQueryResponse::TerminalParameterQueryResponse(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

TerminalParameterQueryResponse::TerminalParameterQueryResponse(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void TerminalParameterQueryResponse::parse()
{
    uint8_t* data = m_rawData.data();
    int pos = 0;
    uint32_t id = 0;
    uint8_t len = 0;
    std::vector<uint8_t> value;

    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
    m_length = data[pos++];

    for (int i = 0; i < m_length; i++) {
        id = Utils::endianSwap32(data + pos);
        pos += sizeof(id);
        len = data[pos++];
        value.assign(data + pos, data + pos + len);
        pos += len;

        m_params[id] = value;
    }

    m_isValid = true;
}

void TerminalParameterQueryResponse::package()
{
    Utils::U16Array u16Data = {0};
    Utils::U32Array u32Data = {0};

    m_rawData.clear();

    u16Data.value = Utils::endianSwap16(m_seq);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    m_rawData.push_back(m_length);

    for (auto& item : m_params) {
        u32Data.value = Utils::endianSwap32(item.first);
        m_rawData.insert(m_rawData.end(), u32Data.array, u32Data.array + sizeof(u32Data));

        m_rawData.push_back(item.second.size());

        m_rawData.insert(m_rawData.end(), item.second.begin(), item.second.end());
    }

    m_isValid = true;
}

uint16_t TerminalParameterQueryResponse::seq() const
{
    return m_seq;
}

void TerminalParameterQueryResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

uint8_t TerminalParameterQueryResponse::length() const
{
    return m_length;
}

void TerminalParameterQueryResponse::setLength(uint8_t newLength)
{
    m_length = newLength;
}

TerminalParameters TerminalParameterQueryResponse::params() const
{
    return m_params;
}

void TerminalParameterQueryResponse::setParams(const TerminalParameters& newParams)
{
    m_params = newParams;
}

}
}
