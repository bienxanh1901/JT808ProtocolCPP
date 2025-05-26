#include "JT808/MessageBody/ElectronicWaybillReport.h"

namespace JT808::MessageBody {

ElectronicWaybillReport::ElectronicWaybillReport(const std::string& data)
    : MessageBodyBase()
    , m_length(data.length())
    , m_data(data)
{
}

void ElectronicWaybillReport::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void ElectronicWaybillReport::parse(const uint8_t* data, int size)
{
    int pos = 0;
    m_length = Utils::endianSwap32(data + pos);
    pos += sizeof(m_length);
    m_data.assign(data + pos, data + size);

    setIsValid(true);
}

std::vector<uint8_t> ElectronicWaybillReport::package()
{
    std::vector<uint8_t> result;

    Utils::appendU32(m_length, result);

    result.insert(result.end(), m_data.begin(), m_data.end());

    return result;
}

bool ElectronicWaybillReport::operator==(const ElectronicWaybillReport& other)
{
    return m_length == other.m_length && m_data == other.m_data;
}

uint32_t ElectronicWaybillReport::length() const
{
    return m_length;
}

void ElectronicWaybillReport::setLength(uint32_t newLength)
{
    m_length = newLength;
}

std::string ElectronicWaybillReport::data() const
{
    return m_data;
}

void ElectronicWaybillReport::setData(const std::string& newData)
{
    m_data = newData;
}

}
