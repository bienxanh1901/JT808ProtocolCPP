#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include <cstdint>

#include "JT808/MessageBody/ElectronicWaybillReport.h"
#include "JT808/Schema/ElectronicWaybillReportSchema.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

ElectronicWaybillReport::ElectronicWaybillReport()
    : MessageBodyBase(Schema::ElectronicWaybillReportSchema)
{
}

ElectronicWaybillReport::ElectronicWaybillReport(const ByteArray& data)
    : MessageBodyBase(Schema::ElectronicWaybillReportSchema)
    , m_data(data)
{
}

void ElectronicWaybillReport::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void ElectronicWaybillReport::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    // lengthconst
    uint32_t const length = Utils::endianSwap32(data + pos);
    pos += sizeof(length);
    // data
    m_data.assign(data + pos, data + pos + length);

    setIsValid(true);
}

ByteArray ElectronicWaybillReport::package()
{
    ByteArray result;
    // length
    Utils::appendU32(m_data.size(), result);
    // data
    Utils::append(m_data, result);

    return result;
}

bool ElectronicWaybillReport::operator==(const ElectronicWaybillReport& other) const
{
    return m_data == other.m_data;
}

void ElectronicWaybillReport::fromJson(const Json& data)
{
    if (validate(data)) {
        m_data = data["data"].get<ByteArray>();
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json ElectronicWaybillReport::toJson()
{
    return Json::object({{"length", m_data.size()}, {"data", m_data}});
}

ByteArray ElectronicWaybillReport::data() const
{
    return m_data;
}

void ElectronicWaybillReport::setData(const ByteArray& newData)
{
    m_data = newData;
}

}
