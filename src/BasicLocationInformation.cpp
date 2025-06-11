#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/BCD.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/LocationInformationCommon.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>

namespace JT808::MessageBody {

BasicLocationInformation::BasicLocationInformation(const AlarmFlags& alarm, const StatusFlags& status, uint32_t lat,
                                                   uint32_t lng, uint16_t alt, uint16_t speed, uint16_t bearing,
                                                   std::string time)
    : m_alarm(alarm)
    , m_status(status)
    , m_lat(lat)
    , m_lng(lng)
    , m_alt(alt)
    , m_speed(speed)
    , m_bearing(bearing)
    , m_time(std::move(time))
{
}

bool BasicLocationInformation::operator==(const BasicLocationInformation& other) const
{
    return m_alarm.value == other.m_alarm.value && m_status.value == other.m_status.value && m_lat == other.m_lat
        && m_lng == other.m_lng && m_alt == other.m_alt && m_speed == other.m_speed && m_bearing == other.m_bearing
        && m_time == other.m_time;
}

int BasicLocationInformation::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;

    // alarm
    m_alarm.value = Utils::endianSwap32(data + pos);
    pos += sizeof(m_alarm);
    // status
    m_status.value = Utils::endianSwap32(data + pos);
    pos += sizeof(m_status);
    // latitude
    m_lat = Utils::endianSwap32(data + pos);
    pos += sizeof(m_lat);
    // longitude
    m_lng = Utils::endianSwap32(data + pos);
    pos += sizeof(m_lng);
    // altitude
    m_alt = Utils::endianSwap16(data + pos);
    pos += sizeof(m_alt);
    // speed
    m_speed = Utils::endianSwap16(data + pos);
    pos += sizeof(m_speed);
    // bearing
    m_bearing = Utils::endianSwap16(data + pos);
    pos += sizeof(m_bearing);
    // time
    m_time = BCD::toString(data + pos, 6);
    pos += 6;

    return pos;
}

ByteArray BasicLocationInformation::package()
{
    ByteArray result;

    // alarm
    Utils::appendU32(m_alarm.value, result);
    // status
    Utils::appendU32(m_status.value, result);
    // lat
    Utils::appendU32(m_lat, result);
    // lng
    Utils::appendU32(m_lng, result);
    // alt
    Utils::appendU16(m_alt, result);
    // speed
    Utils::appendU16(m_speed, result);
    // bearing
    Utils::appendU16(m_bearing, result);
    // time
    Utils::appendBCD(m_time, result);

    return result;
}

void BasicLocationInformation::fromJson(const Json& data)
{
    m_alarm.value = data["alarm"];
    m_status.value = data["status"];
    m_lat = data["latitude"];
    m_lng = data["longitude"];
    m_alt = data["altitude"];
    m_speed = data["speed"];
    m_bearing = data["bearing"];
    m_time = data["time"];
}

Json BasicLocationInformation::toJson()
{
    return Json::object({{"alarm", m_alarm.value},
                         {"status", m_status.value},
                         {"latitude", m_lat},
                         {"longitude", m_lng},
                         {"altitude", m_alt},
                         {"speed", m_speed},
                         {"bearing", m_bearing},
                         {"time", m_time}});
}

AlarmFlags BasicLocationInformation::alarm() const
{
    return m_alarm;
}

void BasicLocationInformation::setAlarm(const AlarmFlags& newAlarm)
{
    m_alarm = newAlarm;
}

StatusFlags BasicLocationInformation::status() const
{
    return m_status;
}

void BasicLocationInformation::setStatus(const StatusFlags& newStatus)
{
    m_status = newStatus;
}

uint32_t BasicLocationInformation::lat() const
{
    return m_lat;
}

void BasicLocationInformation::setLat(uint32_t newLat)
{
    m_lat = newLat;
}

uint32_t BasicLocationInformation::lng() const
{
    return m_lng;
}

void BasicLocationInformation::setLng(uint32_t newLng)
{
    m_lng = newLng;
}

uint16_t BasicLocationInformation::alt() const
{
    return m_alt;
}

void BasicLocationInformation::setAlt(uint16_t newAlt)
{
    m_alt = newAlt;
}

uint16_t BasicLocationInformation::speed() const
{
    return m_speed;
}

void BasicLocationInformation::setSpeed(uint16_t newSpeed)
{
    m_speed = newSpeed;
}

uint16_t BasicLocationInformation::bearing() const
{
    return m_bearing;
}

void BasicLocationInformation::setBearing(uint16_t newBearing)
{
    m_bearing = newBearing;
}

std::string BasicLocationInformation::time() const
{
    return m_time;
}

void BasicLocationInformation::setTime(const std::string& newTime)
{
    m_time = newTime;
}
}
