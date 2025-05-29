#include "JT808/MessageBody/LocationInformationReport.h"
#include "JT808/MessageBody/LocationInformation.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace {
nlohmann::json schema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Location Information",
    "properties": {
        "alarm": {
            "description": "Alarm Flag",
            "type": "number"
        },
        "status": {
            "description": "Status",
            "type": "number"
        },
        "latitude": {
            "description": "Latitude",
            "type": "number"
        },
        "longitude": {
            "description": "Longitude",
            "type": "number"
        },
        "altitude": {
            "description": "Altitude",
            "type": "number"
        },
        "speed": {
            "description": "Speed",
            "type": "number"
        },
        "bearing": {
            "description": "Direction",
            "type": "number"
        },
        "time": {
            "description": "Time",
            "type": "string"
        },
        "extra": {
            "description": "Additional Location Information Items",
            "type": "object"
        }
    },
    "required": ["alarm", "status", "latitude", "longitude", "altitude", "speed", "bearing", "time"],
    "type": "object"
}

)"_json;
}

namespace JT808::MessageBody {

LocationInformationReport::LocationInformationReport()
    : MessageBodyBase(schema)
{
}

LocationInformationReport::LocationInformationReport(const nlohmann::json& schema)
    : MessageBodyBase(schema)
{
}

LocationInformationReport::LocationInformationReport(const AlarmFlags& alarm, const StatusFlags& status, uint32_t lat,
                                                     uint32_t lng, uint16_t alt, uint16_t speed, uint16_t bearing,
                                                     const std::string& time, const ExtraInfo& extra)
    : MessageBodyBase(schema)
    , m_info(alarm, status, lat, lng, alt, speed, bearing, time, extra)
{
}

LocationInformationReport::LocationInformationReport(const nlohmann::json& schema, const AlarmFlags& alarm,
                                                     const StatusFlags& status, uint32_t lat, uint32_t lng,
                                                     uint16_t alt, uint16_t speed, uint16_t bearing,
                                                     const std::string& time, const ExtraInfo& extra)
    : MessageBodyBase(schema)
    , m_info(alarm, status, lat, lng, alt, speed, bearing, time, extra)
{
}

LocationInformationReport::LocationInformationReport(const nlohmann::json& schema, LocationInformation info)
    : MessageBodyBase(schema)
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
