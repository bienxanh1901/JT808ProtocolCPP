#include "JT808/MessageBody/SettingRoute.h"
#include "JT808/BCD.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/AreaSettingProperties.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/SettingRouteSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

SettingRoute::SettingRoute()
    : MessageBodyBase(Schema::SettingRouteSchema)
{
}

SettingRoute::SettingRoute(uint32_t id, AreaProperties flag, std::string startTime, std::string endTime,
                           const std::vector<Point>& points)
    : MessageBodyBase(Schema::SettingRouteSchema)
    , m_id(id)
    , m_flag(flag)
    , m_startTime(std::move(startTime))
    , m_endTime(std::move(endTime))
    , m_points(points)
{
}

void SettingRoute::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void SettingRoute::parse(const uint8_t* data, int size)
{
    int pos = 0;
    int pos1 = 0;
    uint16_t length = 0;

    // id
    m_id = Utils::endianSwap32(data + pos);
    pos += sizeof(m_id);
    // flag
    m_flag.value = Utils::endianSwap16(data + pos);
    pos += sizeof(m_flag);
    // time
    if (m_flag.bits.areaTime == 1) {
        m_startTime = BCD::toString(data + pos, 6);
        pos += 6;
        m_endTime = BCD::toString(data + pos, 6);
        pos += 6;
    }
    // length
    length = Utils::endianSwap16(data + pos);
    pos += sizeof(length);
    // points
    for (int i = 0; i < length; i++) {

        Point item = {0};
        pos1 = item.parse(data + pos, size);
        pos += pos1;
        m_points.push_back(item);
    }

    setIsValid(true);
}

ByteArray SettingRoute::package()
{
    ByteArray result;
    // id
    Utils::appendU32(m_id, result);
    // flag
    Utils::appendU16(m_flag.value, result);
    // time
    if (m_flag.bits.areaTime == 1) {
        Utils::appendBCD(m_startTime, result);
        Utils::appendBCD(m_endTime, result);
    }
    // length
    Utils::appendU16(m_points.size(), result);
    // points
    for (auto& item : m_points) {
        Utils::append(item.package(), result);
    }

    return result;
}

bool SettingRoute::operator==(const SettingRoute& other) const
{
    return m_id == other.m_id && m_flag.value == other.m_flag.value && m_startTime == other.m_startTime
        && m_endTime == other.m_endTime && m_points == other.m_points;
}

void SettingRoute::fromJson(const Json& data)
{
    if (validate(data)) {
        m_id = data["id"];
        m_flag.value = data["flag"];

        if (m_flag.bits.areaTime == 1) {
            m_startTime = data["start_time"];
            m_endTime = data["end_time"];
        }

        if (data["length"] > 0) {
            for (auto& point : data["points"]) {
                Point item = {0};
                item.fromJson(point);
                m_points.push_back(item);
            }
        }

        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json SettingRoute::toJson()
{
    Json result({{"id", m_id}, {"flag", m_flag.value}});
    if (m_flag.bits.areaTime == 1) {
        result["start_time"] = m_startTime;
        result["end_time"] = m_endTime;
    }

    result["length"] = m_points.size();
    result["points"] = {};
    for (auto& item : m_points) {
        result["points"].push_back(item.toJson());
    }

    return result;
}

uint32_t SettingRoute::id() const
{
    return m_id;
}

void SettingRoute::setId(uint32_t newId)
{
    m_id = newId;
}

AreaProperties SettingRoute::flag() const
{
    return m_flag;
}

void SettingRoute::setFlag(const AreaProperties& newFlag)
{
    m_flag = newFlag;
}

std::string SettingRoute::startTime() const
{
    return m_startTime;
}

void SettingRoute::setStartTime(const std::string& newStartTime)
{
    m_startTime = newStartTime;
}

std::string SettingRoute::endTime() const
{
    return m_endTime;
}

void SettingRoute::setEndTime(const std::string& newEndTime)
{
    m_endTime = newEndTime;
}

std::vector<SettingRoute::Point> SettingRoute::points() const
{
    return m_points;
}

void SettingRoute::setPoints(const std::vector<Point>& newPoints)
{
    m_points = newPoints;
}

bool SettingRoute::Point::operator==(const Point& other) const
{
    return pointId == other.pointId && routeId == other.routeId && flag.value == other.flag.value && lat == other.lat
        && lng == other.lng && width == other.width && maxDrivingTime == other.maxDrivingTime
        && minDrivingTime == other.minDrivingTime && maxSpeed == other.maxSpeed
        && overspeedDuration == other.overspeedDuration;
}

int SettingRoute::Point::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    // point id
    pointId = Utils::endianSwap32(data + pos);
    pos += sizeof(pointId);
    // route id
    routeId = Utils::endianSwap32(data + pos);
    pos += sizeof(routeId);
    // lat
    lat = Utils::endianSwap32(data + pos);
    pos += sizeof(lat);
    // lng
    lng = Utils::endianSwap32(data + pos);
    pos += sizeof(lng);
    // width
    width = data[pos++];
    // flag
    flag.value = data[pos++];
    // time
    if (flag.bits.drivingTime == 1) {
        maxDrivingTime = Utils::endianSwap16(data + pos);
        pos += sizeof(maxDrivingTime);
        minDrivingTime = Utils::endianSwap16(data + pos);
        pos += sizeof(minDrivingTime);
    }
    // speed
    if (flag.bits.speedLimit == 1) {
        maxSpeed = Utils::endianSwap16(data + pos);
        pos += sizeof(maxSpeed);
        overspeedDuration = data[pos++];
    }

    return pos;
}

ByteArray SettingRoute::Point::package() const
{
    ByteArray result;
    // point id
    Utils::appendU32(pointId, result);
    // route id
    Utils::appendU32(routeId, result);
    // lat
    Utils::appendU32(lat, result);
    // lng
    Utils::appendU32(lng, result);
    // route width
    result.push_back(width);
    // flag
    result.push_back(flag.value);
    // time
    if (flag.bits.drivingTime == 1) {
        Utils::appendU16(maxDrivingTime, result);
        Utils::appendU16(minDrivingTime, result);
    }
    // speed
    if (flag.bits.speedLimit == 1) {
        Utils::appendU16(maxSpeed, result);
        result.push_back(overspeedDuration);
    }
    return result;
}

void SettingRoute::Point::fromJson(const Json& data)
{
    pointId = data["point_id"];
    routeId = data["route_id"];
    lat = data["lat"];
    lng = data["lng"];
    width = data["width"];
    flag.value = data["flag"];

    if (flag.bits.drivingTime == 1) {
        maxDrivingTime = data["passed"];
        minDrivingTime = data["uncovered"];
    }

    if (flag.bits.speedLimit == 1) {
        maxSpeed = data["max_speed"];
        overspeedDuration = data["overspeed_duration"];
    }
}

Json SettingRoute::Point::toJson()
{
    Json result({{"point_id", pointId},
                 {"route_id", routeId},
                 {"lat", lat},
                 {"lng", lng},
                 {"width", width},
                 {"flag", flag.value}});

    if (flag.bits.drivingTime == 1) {
        result["passed"] = maxDrivingTime;
        result["uncovered"] = minDrivingTime;
    }

    if (flag.bits.speedLimit == 1) {
        result["max_speed"] = maxSpeed;
        result["overspeed_duration"] = overspeedDuration;
    }

    return result;
}

}
