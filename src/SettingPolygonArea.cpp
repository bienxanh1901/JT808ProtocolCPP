#include "JT808/MessageBody/SettingPolygonArea.h"
#include "JT808/BCD.h"
#include "JT808/MessageBody/AreaSettingProperties.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/SettingPolygonAreaSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

SettingPolygonArea::SettingPolygonArea()
    : MessageBodyBase(Schema::SettingPolygonAreaSchema)
{
}

SettingPolygonArea::SettingPolygonArea(uint32_t id, AreaProperties flag, std::string startTime, std::string endTime,
                                       uint16_t maxSpeed, uint8_t overspeedDuration, const std::vector<Point>& points)
    : MessageBodyBase(Schema::SettingPolygonAreaSchema)
    , m_id(id)
    , m_flag(flag)
    , m_startTime(std::move(startTime))
    , m_endTime(std::move(endTime))
    , m_maxSpeed(maxSpeed)
    , m_overspeedDuration(overspeedDuration)
    , m_points(points)
{
}

void SettingPolygonArea::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void SettingPolygonArea::parse(const uint8_t* data, int size)
{
    int pos = 0;
    int pos1 = 0;
    uint16_t length = 0;
    Point item = {0};
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
    // speed
    if (m_flag.bits.speedLimit == 1) {
        m_maxSpeed = Utils::endianSwap16(data + pos);
        pos += sizeof(m_maxSpeed);
        m_overspeedDuration = data[pos++];
    }
    // length
    length = data[pos++];
    // points
    for (int i = 0; i < length; i++) {
        pos1 = item.parse(data + pos, size);
        pos += pos1;

        m_points.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> SettingPolygonArea::package()
{
    std::vector<uint8_t> result;
    // id
    Utils::appendU32(m_id, result);
    // flag
    Utils::appendU16(m_flag.value, result);
    // time
    if (m_flag.bits.areaTime == 1) {
        Utils::appendBCD(m_startTime, result);
        Utils::appendBCD(m_endTime, result);
    }
    // speed
    if (m_flag.bits.speedLimit == 1) {
        Utils::appendU16(m_maxSpeed, result);
        result.push_back(m_overspeedDuration);
    }
    // length
    result.push_back(m_points.size());
    // points
    for (auto& item : m_points) {
        Utils::append(item.package(), result);
    }

    return result;
}

bool SettingPolygonArea::operator==(const SettingPolygonArea& other) const
{
    return m_id == other.m_id && m_flag.value == other.m_flag.value && m_startTime == other.m_startTime
        && m_endTime == other.m_endTime && m_maxSpeed == other.m_maxSpeed
        && m_overspeedDuration == other.m_overspeedDuration && m_points == other.m_points;
}

void SettingPolygonArea::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_id = data["id"];
        m_flag.value = data["flag"];

        if (m_flag.bits.areaTime == 1) {
            m_startTime = data["start_time"];
            m_endTime = data["end_time"];
        }

        if (m_flag.bits.speedLimit == 1) {
            m_maxSpeed = data["max_speed"];
            m_overspeedDuration = data["overspeed_duration"];
        }

        if (data["length"] > 0) {
            Point item = {0};

            for (auto& point : data["points"]) {
                item.fromJson(point);
                m_points.push_back(item);
            }
        }

        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json SettingPolygonArea::toJson()
{
    nlohmann::json result({{"id", m_id}, {"flag", m_flag.value}});
    if (m_flag.bits.areaTime == 1) {
        result["start_time"] = m_startTime;
        result["end_time"] = m_endTime;
    }

    if (m_flag.bits.speedLimit == 1) {
        result["max_speed"] = m_maxSpeed;
        result["overspeed_duration"] = m_overspeedDuration;
    }

    result["length"] = m_points.size();
    result["points"] = {};
    for (auto& item : m_points) {
        result["points"].push_back(item.toJson());
    }

    return result;
}

uint32_t SettingPolygonArea::id() const
{
    return m_id;
}

void SettingPolygonArea::setId(uint32_t newId)
{
    m_id = newId;
}

AreaProperties SettingPolygonArea::flag() const
{
    return m_flag;
}

void SettingPolygonArea::setFlag(const AreaProperties& newFlag)
{
    m_flag = newFlag;
}

std::string SettingPolygonArea::startTime() const
{
    return m_startTime;
}

void SettingPolygonArea::setStartTime(const std::string& newStartTime)
{
    m_startTime = newStartTime;
}

std::string SettingPolygonArea::endTime() const
{
    return m_endTime;
}

void SettingPolygonArea::setEndTime(const std::string& newEndTime)
{
    m_endTime = newEndTime;
}

uint16_t SettingPolygonArea::maxSpeed() const
{
    return m_maxSpeed;
}

void SettingPolygonArea::setMaxSpeed(uint16_t newMaxSpeed)
{
    m_maxSpeed = newMaxSpeed;
}

uint8_t SettingPolygonArea::overspeedDuration() const
{
    return m_overspeedDuration;
}

void SettingPolygonArea::setOverspeedDuration(uint8_t newOverspeedDuration)
{
    m_overspeedDuration = newOverspeedDuration;
}

std::vector<SettingPolygonArea::Point> SettingPolygonArea::points() const
{
    return m_points;
}

void SettingPolygonArea::setPoints(const std::vector<Point>& newPoints)
{
    m_points = newPoints;
}

bool SettingPolygonArea::Point::operator==(const Point& other) const
{
    return lat == other.lat && lng == other.lng;
}

int SettingPolygonArea::Point::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    lat = Utils::endianSwap32(data + pos);
    pos += sizeof(lat);
    lng = Utils::endianSwap32(data + pos);
    pos += sizeof(lng);
    return pos;
}

std::vector<uint8_t> SettingPolygonArea::Point::package() const
{
    std::vector<uint8_t> result;
    Utils::appendU32(lat, result);
    Utils::appendU32(lng, result);
    return result;
}

void SettingPolygonArea::Point::fromJson(const nlohmann::json& data)
{
    lat = data["lat"];
    lng = data["lng"];
}

nlohmann::json SettingPolygonArea::Point::toJson()
{
    return {{"lat", lat}, {"lng", lng}};
}

}
