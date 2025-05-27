#include "JT808/MessageBody/DataCompressionReport.h"

namespace JT808::MessageBody {

DataCompressionReport::DataCompressionReport(const std::vector<uint8_t>& data)
    : MessageBodyBase()
    , m_data(data)
{
}

void DataCompressionReport::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void DataCompressionReport::parse(const uint8_t* data, int size)
{
    int pos = 0;

    // length
    uint32_t length = Utils::endianSwap32(data);
    pos += sizeof(length);
    m_data.assign(data + pos, data + size);

    setIsValid(true);
}

std::vector<uint8_t> DataCompressionReport::package()
{
    std::vector<uint8_t> result;

    Utils::appendU32(m_data.size(), result);
    result.insert(result.end(), m_data.begin(), m_data.end());

    return result;
}

bool DataCompressionReport::operator==(const DataCompressionReport& other)
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
