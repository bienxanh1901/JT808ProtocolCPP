#include "JT808/MessageBody/DataCompressionReport.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/DataCompressionReportSchema.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

DataCompressionReport::DataCompressionReport()
    : MessageBodyBase(Schema::DataCompressionReportSchema)
{
}

DataCompressionReport::DataCompressionReport(const ByteArray& data)
    : MessageBodyBase(Schema::DataCompressionReportSchema)
    , m_data(data)
{
}

void DataCompressionReport::parse(const ByteArray& data)
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

ByteArray DataCompressionReport::package()
{
    ByteArray result;
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

void DataCompressionReport::fromJson(const Json& data)
{
    if (validate(data)) {
        m_data = data["data"].get<ByteArray>();
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json DataCompressionReport::toJson()
{
    return {{"data", m_data}};
}

ByteArray DataCompressionReport::data() const
{
    return m_data;
}

void DataCompressionReport::setData(const ByteArray& newData)
{
    m_data = newData;
}

}
