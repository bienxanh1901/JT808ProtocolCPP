#include "JT808/MessageBody/DataTransmission.h"

namespace JT808::MessageBody {

DataTransmission::DataTransmission(uint8_t type, const std::vector<uint8_t>& data)
    : MessageBodyBase()
    , m_type(type)
    , m_data(data)
{
}

void DataTransmission::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void DataTransmission::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // type
    m_type = data[pos++];
    // data
    m_data.assign(data + pos, data + size);

    setIsValid(true);
}

std::vector<uint8_t> DataTransmission::package()
{
    std::vector<uint8_t> result;
    // type
    result.push_back(m_type);
    // data
    result.insert(result.end(), m_data.begin(), m_data.end());

    return result;
}

bool DataTransmission::operator==(const DataTransmission& other)
{
    return m_type == other.m_type && m_data == other.m_data;
}

uint8_t DataTransmission::type() const
{
    return m_type;
}

void DataTransmission::setType(uint8_t newType)
{
    m_type = newType;
}

std::vector<uint8_t> DataTransmission::data() const
{
    return m_data;
}

void DataTransmission::setData(const std::vector<uint8_t>& newData)
{
    m_data = newData;
}

}
