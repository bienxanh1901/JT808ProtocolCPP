#include "JT808/MessageBody/TerminalParameterSetting.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

TerminalParameterSetting::TerminalParameterSetting(const TerminalParameters& params)
    : MessageBodyBase()
    , m_length(params.size())
    , m_params(params)
{
}

void TerminalParameterSetting::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalParameterSetting::parse(const uint8_t* data, int size)
{
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

    setIsValid(true);
}

std::vector<uint8_t> TerminalParameterSetting::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_length);

    for (auto& item : m_params) {
        Utils::appendU32(item.first, result);
        result.push_back(item.second.size());
        result.insert(result.end(), item.second.begin(), item.second.end());
    }

    return result;
}

bool TerminalParameterSetting::operator==(const TerminalParameterSetting& other)
{
    return m_length == other.m_length && m_params == other.m_params;
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
