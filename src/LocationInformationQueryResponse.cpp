#include "JT808/MessageBody/LocationInformationQueryResponse.h"
#include "JT808/MessageBody/LocationInformation.h"
#include "JT808/MessageBody/LocationInformationReport.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <vector>

namespace {
nlohmann::json schema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Location Information Query Response",
    "properties": {
        "seq": {
            "description": "Message Serial Number",
            "type": "integer"
        },
        "params": {
            "description": "Location Information Report",
            "type": "object",
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
            "required": [
                "alarm",
                "status",
                "latitude",
                "longitude",
                "altitude",
                "speed",
                "bearing",
                "time"
            ]
        }
    },
    "required": [
        "seq",
        "params"
    ],
    "type": "object"
}

)"_json;
}

namespace JT808::MessageBody {

LocationInformationQueryResponse::LocationInformationQueryResponse()
    : LocationInformationReport(schema)
{
}

LocationInformationQueryResponse::LocationInformationQueryResponse(const LocationInformation& info)
    : LocationInformationReport(schema, info)
{
}

LocationInformationQueryResponse::LocationInformationQueryResponse(uint16_t seq, const AlarmFlags& alarm,
                                                                   const StatusFlags& status, uint32_t lat,
                                                                   uint32_t lng, uint16_t alt, uint16_t speed,
                                                                   uint16_t bearing, const std::string& time,
                                                                   const ExtraInfo& extra)
    : m_seq(seq)
    , LocationInformationReport(schema, alarm, status, lat, lng, alt, speed, bearing, time, extra)
{
}

void LocationInformationQueryResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void LocationInformationQueryResponse::parse(const uint8_t* data, int size)
{
    m_seq = Utils::endianSwap16(data);
    LocationInformationReport::parse(data + 2, size - 2);
}

std::vector<uint8_t> LocationInformationQueryResponse::package()
{
    std::vector<uint8_t> result;

    Utils::appendU16(m_seq, result);
    Utils::append(LocationInformationReport::package(), result);

    return result;
}

bool LocationInformationQueryResponse::operator==(const LocationInformationQueryResponse& other) const
{
    return m_seq == other.m_seq && LocationInformationReport::operator==(other);
}

void LocationInformationQueryResponse::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        LocationInformationReport::fromJson(data["param"]);
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json LocationInformationQueryResponse::toJson()
{
    return {{"seq", m_seq}, "params", LocationInformationReport::toJson()};
}

uint16_t LocationInformationQueryResponse::seq() const
{
    return m_seq;
}

void LocationInformationQueryResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}
}
