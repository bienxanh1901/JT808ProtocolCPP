#include "JT808/MessageBody/DataCompressionReport.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

DataCompressionReport::DataCompressionReport(const std::vector<uint8_t>& data)
    : m_data(data)
{
}

void DataCompressionReport::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void DataCompressionReport::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;

    // length
    uint32_t const length = Utils::endianSwap32(data);
    pos += sizeof(length);
    // data
    m_data.assign(data + pos, data + pos + length);

    setIsValid(true);
}

std::vector<uint8_t> DataCompressionReport::package()
{
    std::vector<uint8_t> result;
    // length
    Utils::appendU32(m_data.size(), result);
    // data
    Utils::append(m_data, result);

    return result;
}

bool DataCompressionReport::operator==(const DataCompressionReport& other) const
{
    return m_data == other.m_data;
}

std::vector<uint8_t> DataCompressionReport::data() const
{
    return m_data;
}

void DataCompressionReport::setData(const std::vector<uint8_t>& newData)
{
    m_data = newData;
}

}
