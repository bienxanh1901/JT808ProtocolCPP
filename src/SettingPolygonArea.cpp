#include "JT808/MessageBody/SettingPolygonArea.h"
#include "JT808/BCD.h"

namespace JT808::MessageBody {

SettingPolygonArea::SettingPolygonArea(uint32_t id, AreaProperties flag, const std::string& startTime,
                                       const std::string& endTime, uint16_t maxSpeed, uint8_t overspeedDuration,
                                       const std::vector<Point> points)
    : MessageBodyBase()
    , m_id(id)
    , m_flag(flag)
    , m_startTime(startTime)
    , m_endTime(endTime)
    , m_maxSpeed(maxSpeed)
    , m_overspeedDuration(overspeedDuration)
    , m_length(points.size())
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
    Point item = {0};

    m_id = Utils::endianSwap32(data + pos);
    pos += sizeof(m_id);
    m_flag.value = Utils::endianSwap16(data + pos);
    pos += sizeof(m_flag);

    if (m_flag.bits.areaTime == 1) {
        m_startTime = BCD::toString(data + pos, 6);
        pos += 6;
        m_endTime = BCD::toString(data + pos, 6);
        pos += 6;
    }

    if (m_flag.bits.speedLimit == 1) {
        m_maxSpeed = Utils::endianSwap16(data + pos);
        pos += sizeof(m_maxSpeed);
        m_overspeedDuration = data[pos++];
    }

    m_length = data[pos++];

    for (int i = 0; i < m_length; i++) {

        item.lat = Utils::endianSwap32(data + pos);
        pos += sizeof(item.lat);
        item.lng = Utils::endianSwap32(data + pos);
        pos += sizeof(item.lng);

        m_points.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> SettingPolygonArea::package()
{
    std::vector<uint8_t> result;

    Utils::appendU32(m_id, result);
    Utils::appendU16(m_flag.value, result);

    if (m_flag.bits.areaTime == 1) {
        Utils::appendBCD(m_startTime, result);
        Utils::appendBCD(m_endTime, result);
    }

    if (m_flag.bits.speedLimit == 1) {
        Utils::appendU16(m_maxSpeed, result);
        result.push_back(m_overspeedDuration);
    }

    result.push_back(m_length);

    for (auto& item : m_points) {
        Utils::appendU32(item.lat, result);
        Utils::appendU32(item.lng, result);
    }

    return result;
}

bool SettingPolygonArea::operator==(const SettingPolygonArea& other)
{
    return m_id == other.m_id && m_flag.value == other.m_flag.value && m_startTime == other.m_startTime
        && m_endTime == other.m_endTime && m_maxSpeed == other.m_maxSpeed
        && m_overspeedDuration == other.m_overspeedDuration && m_length == other.m_length && m_points == other.m_points;
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

uint16_t SettingPolygonArea::length() const
{
    return m_length;
}

void SettingPolygonArea::setLength(uint16_t newLength)
{
    m_length = newLength;
}

std::vector<SettingPolygonArea::Point> SettingPolygonArea::points() const
{
    return m_points;
}

void SettingPolygonArea::setPoints(const std::vector<Point>& newPoints)
{
    m_points = newPoints;
}

}
