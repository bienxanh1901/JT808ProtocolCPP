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

std::vector<uint8_t> SettingRoute::package()
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
    return id == other.id && flag.value == other.flag.value && lat == other.lat && lng == other.lng
        && width == other.width && maxDrivingTime == other.maxDrivingTime && minDrivingTime == other.minDrivingTime
        && maxSpeed == other.maxSpeed && overspeedDuration == other.overspeedDuration;
}

int SettingRoute::Point::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // id
    id = Utils::endianSwap32(data + pos);
    pos += sizeof(id);
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

std::vector<uint8_t> SettingRoute::Point::package()
{
    std::vector<uint8_t> result;
    Utils::appendU32(id, result);
    Utils::appendU32(lat, result);
    Utils::appendU32(lng, result);
    result.push_back(width);
    result.push_back(flag.value);

    if (flag.bits.drivingTime == 1) {
        Utils::appendU16(maxDrivingTime, result);
        Utils::appendU16(minDrivingTime, result);
    }

    if (flag.bits.speedLimit == 1) {
        Utils::appendU16(maxSpeed, result);
        result.push_back(overspeedDuration);
    }
    return result;
}

}
