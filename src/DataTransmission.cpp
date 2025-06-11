#include "JT808/MessageBody/DataTransmission.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/DataTransmissionSchema.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

DataTransmission::DataTransmission()
    : MessageBodyBase(Schema::DataTransmissionSchema)
{
}

DataTransmission::DataTransmission(uint8_t type, const ByteArray& data)
    : MessageBodyBase(Schema::DataTransmissionSchema)
    , m_type(type)
    , m_data(data)
{
}

void DataTransmission::parse(const ByteArray& data)
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

ByteArray DataTransmission::package()
{
    ByteArray result;
    // type
    result.push_back(m_type);
    // data
    Utils::append(m_data, result);

    return result;
}

bool DataTransmission::operator==(const DataTransmission& other) const
{
    return m_type == other.m_type && m_data == other.m_data;
}

void DataTransmission::fromJson(const Json& data)
{
    if (validate(data)) {
        m_type = data["type"];
        m_data = data["data"].get<ByteArray>();
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json DataTransmission::toJson()
{
    return {{"type", m_type}, {"data", m_data}};
}

uint8_t DataTransmission::type() const
{
    return m_type;
}

void DataTransmission::setType(uint8_t newType)
{
    m_type = newType;
}

ByteArray DataTransmission::data() const
{
    return m_data;
}

void DataTransmission::setData(const ByteArray& newData)
{
    m_data = newData;
}

}
