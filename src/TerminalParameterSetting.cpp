#include "JT808/MessageBody/TerminalParameterSetting.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {

TerminalParameterSetting::TerminalParameterSetting(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

TerminalParameterSetting::TerminalParameterSetting(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void TerminalParameterSetting::parse()
{
    uint8_t* data = m_rawData.data();
    int pos = 0;

    m_length = data[pos++];

    uint32_t id = 0;
    uint8_t len = 0;
    std::vector<uint8_t> value;

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

void TerminalParameterSetting::package()
{
    Utils::U32Array u32Data = {0};

    m_rawData.clear();

    m_rawData.push_back(m_length);

    for (auto& item : m_params) {
        u32Data.value = Utils::endianSwap32(item.first);
        m_rawData.insert(m_rawData.end(), u32Data.array, u32Data.array + sizeof(u32Data));

        m_rawData.push_back(item.second.size());

        m_rawData.insert(m_rawData.end(), item.second.begin(), item.second.end());
    }

    m_isValid = true;
}

uint8_t TerminalParameterSetting::length() const
{
    return m_length;
}

void TerminalParameterSetting::setLength(uint8_t newLength)
{
    m_length = newLength;
}

TerminalParameters TerminalParameterSetting::params() const
{
    return m_params;
}

void TerminalParameterSetting::setParams(const TerminalParameters& newParams)
{
    m_params = newParams;
}

}
}
