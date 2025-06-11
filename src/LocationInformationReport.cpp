#include "JT808/MessageBody/LocationInformationReport.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "JT808/MessageBody/LocationInformation.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/LocationInformationReportSchema.h"
#include <cstdint>
#include <utility>

namespace JT808::MessageBody {

LocationInformationReport::LocationInformationReport()
    : MessageBodyBase(Schema::LocationInformationReportSchema)
{
}

LocationInformationReport::LocationInformationReport(const BasicLocationInformation& basic,
                                                     const ExtraLocationInformation& extra)
    : MessageBodyBase(Schema::LocationInformationReportSchema)
    , m_info(basic, extra)
{
}

LocationInformationReport::LocationInformationReport(LocationInformation info)
    : MessageBodyBase(Schema::LocationInformationReportSchema)
    , m_info(std::move(info))
{
}

void LocationInformationReport::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void LocationInformationReport::parse(const uint8_t* data, int size)
{

    m_info.parse(data, size);

    setIsValid(true);
}

ByteArray LocationInformationReport::package()
{
    return m_info.package();
}

bool LocationInformationReport::operator==(const LocationInformationReport& other) const
{
    return m_info == other.m_info;
}

void LocationInformationReport::fromJson(const Json& data)
{
    if (validate(data)) {
        m_info.fromJson(data);
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json LocationInformationReport::toJson()
{
    return m_info.toJson();
}

LocationInformation LocationInformationReport::info() const
{
    return m_info;
}

void LocationInformationReport::setInfo(const LocationInformation& newInfo)
{
    m_info = newInfo;
}

}
