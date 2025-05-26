#include "JT808/MessageBody/SettingRoute.h"
#include "JT808/BCD.h"

namespace JT808::MessageBody {

SettingRoute::SettingRoute(uint32_t id, AreaProperties flag, const std::string& startTime, const std::string& endTime,
                           const std::vector<Point>& points)
    : MessageBodyBase()
    , m_id(id)
    , m_flag(flag)
    , m_startTime(startTime)
    , m_endTime(endTime)
    , m_length(points.size())
    , m_points(points)
{
}

void SettingRoute::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void SettingRoute::parse(const uint8_t* data, int size)
{
    int pos = 0;

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

    m_length = data[pos++];

    for (int i = 0; i < m_length; i++) {

        Point item = {0};
        item.id = Utils::endianSwap32(data + pos);
        pos += sizeof(item.id);
        item.lat = Utils::endianSwap32(data + pos);
        pos += sizeof(item.lat);
        item.lng = Utils::endianSwap32(data + pos);
        pos += sizeof(item.lng);
        item.width = data[pos++];
        item.flag.value = data[pos++];

        if (item.flag.bits.drivingTime == 1) {
            item.maxDrivingTime = Utils::endianSwap16(data + pos);
            pos += sizeof(item.maxDrivingTime);
            item.minDrivingTime = Utils::endianSwap16(data + pos);
            pos += sizeof(item.minDrivingTime);
        }

        if (item.flag.bits.speedLimit == 1) {
            item.maxSpeed = Utils::endianSwap16(data + pos);
            pos += sizeof(item.maxSpeed);
            item.overspeedDuration = data[pos++];
        }

        m_points.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> SettingRoute::package()
{
    std::vector<uint8_t> result;

    Utils::appendU32(m_id, result);
    Utils::appendU16(m_flag.value, result);

    if (m_flag.bits.areaTime == 1) {
        Utils::appendBCD(m_startTime, result);
        Utils::appendBCD(m_endTime, result);
    }

    if (m_flag.bits.speedLimit == 1) { }

    result.push_back(m_length);

    for (auto& item : m_points) {
        Utils::appendU32(item.id, result);
        Utils::appendU32(item.lat, result);
        Utils::appendU32(item.lng, result);
        result.push_back(item.width);
        result.push_back(item.flag.value);

        if (item.flag.bits.drivingTime == 1) {
            Utils::appendU16(item.maxDrivingTime, result);
            Utils::appendU16(item.minDrivingTime, result);
        }

        if (item.flag.bits.speedLimit == 1) {
            Utils::appendU16(item.maxSpeed, result);
            result.push_back(item.overspeedDuration);
        }
    }

    return result;
}

bool SettingRoute::operator==(const SettingRoute& other)
{
    return m_id == other.m_id && m_flag.value == other.m_flag.value && m_startTime == other.m_startTime
        && m_endTime == other.m_endTime && m_length == other.m_length && m_points == other.m_points;
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

uint16_t SettingRoute::length() const
{
    return m_length;
}

void SettingRoute::setLength(uint16_t newLength)
{
    m_length = newLength;
}

std::vector<SettingRoute::Point> SettingRoute::points() const
{
    return m_points;
}

void SettingRoute::setPoints(const std::vector<Point>& newPoints)
{
    m_points = newPoints;
}

}
