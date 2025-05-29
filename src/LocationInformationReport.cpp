#include "JT808/MessageBody/LocationInformationReport.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "JT808/MessageBody/LocationInformation.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/LocationInformationReportSchema.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <utility>
#include <vector>

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

void LocationInformationReport::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void LocationInformationReport::parse(const uint8_t* data, int size)
{

    m_info.parse(data, size);

    setIsValid(true);
}

std::vector<uint8_t> LocationInformationReport::package()
{
    return m_info.package();
}

bool LocationInformationReport::operator==(const LocationInformationReport& other) const
{
    return m_info == other.m_info;
}

void LocationInformationReport::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_info.fromJson(data);
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json LocationInformationReport::toJson()
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
