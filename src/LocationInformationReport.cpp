#include "JT808/MessageBody/LocationInformationReport.h"
#include "JT808/BCD.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

LocationInformationReport::LocationInformationReport(const AlarmFlags& alarm, const StatusFlags& status,
                                                     uint32_t latitude, uint32_t longitude, uint16_t altitude,
                                                     uint16_t speed, uint16_t bearing, const std::string& time,
                                                     const ExtraInfo& extra)
    : MessageBodyBase()
    , m_alarm(alarm)
    , m_status(status)
    , m_latitude(latitude)
    , m_longitude(longitude)
    , m_altitude(altitude)
    , m_speed(speed)
    , m_bearing(bearing)
    , m_time(time)
    , m_extra(extra)
{
}

void LocationInformationReport::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void LocationInformationReport::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_alarm.value = Utils::endianSwap32(data + pos);
    pos += sizeof(m_alarm);

    m_status.value = Utils::endianSwap32(data + pos);
    pos += sizeof(m_status);

    m_latitude = Utils::endianSwap32(data + pos);
    pos += sizeof(m_latitude);

    m_longitude = Utils::endianSwap32(data + pos);
    pos += sizeof(m_longitude);

    m_altitude = Utils::endianSwap16(data + pos);
    pos += sizeof(m_altitude);

    m_speed = Utils::endianSwap16(data + pos);
    pos += sizeof(m_speed);

    m_bearing = Utils::endianSwap16(data + pos);
    pos += sizeof(m_bearing);

    m_time = BCD::toString(data + pos, 6);
    pos += 6;

    if (size > pos) {
        // parse extra
        uint8_t id = 0;
        uint8_t len = 0;
        std::vector<uint8_t> value;

        while (pos <= size - 2) {
            id = data[pos++];
            len = data[pos++];
            if (pos > size) {
                break;
            }

            value.assign(data + pos, data + pos + len);
            pos += len;
            m_extra[id] = value;
        }
    }

    setIsValid(true);
}

std::vector<uint8_t> LocationInformationReport::package()
{
    std::vector<uint8_t> result;

    // alarm
    Utils::appendU32(m_alarm.value, result);
    // status
    Utils::appendU32(m_status.value, result);
    // lat
    Utils::appendU32(m_latitude, result);
    // lng
    Utils::appendU32(m_longitude, result);
    // alt
    Utils::appendU16(m_altitude, result);
    // speed
    Utils::appendU16(m_speed, result);
    // bearing
    Utils::appendU16(m_bearing, result);
    // time
    Utils::appendBCD(m_time, result);
    // extra
    if (!m_extra.empty()) {
        std::vector<uint8_t> extraCustom;

        for (auto& item : m_extra) {
            if (item.first <= CustomInfoLengthExtraId) {
                result.push_back(item.first);
                if (item.first == CustomInfoLengthExtraId)
                    continue;
                result.push_back(item.second.size());
                result.insert(result.end(), item.second.begin(), item.second.end());
            } else if (item.first > CustomInfoLengthExtraId) {
                extraCustom.push_back(item.first);
                if (!item.second.empty()) {
                    extraCustom.push_back(item.second.size());
                    extraCustom.insert(extraCustom.end(), item.second.begin(), item.second.end());
                }
            }
        }

        const int len = extraCustom.size();

        if (len >= 256) {
            result.push_back(2);
            result.push_back(len % 65536 / 256);
            result.push_back(len % 256);
        } else if (len > 0) {
            result.push_back(1);
            result.push_back(len % 256);
        } else {
            result.pop_back();
        }

        result.insert(result.end(), extraCustom.begin(), extraCustom.end());
    }

    return result;
}

bool LocationInformationReport::operator==(const LocationInformationReport& other)
{
    return m_alarm.value == other.m_alarm.value && m_status.value == other.m_status.value
        && m_latitude == other.m_latitude && m_longitude == other.m_longitude && m_altitude == other.m_altitude
        && m_speed == other.m_speed && m_bearing == other.m_bearing && m_time == other.m_time
        && m_extra == other.m_extra;
}

AlarmFlags LocationInformationReport::alarm() const
{
    return m_alarm;
}

void LocationInformationReport::setAlarm(const AlarmFlags& newAlarm)
{
    m_alarm = newAlarm;
}

StatusFlags LocationInformationReport::status() const
{
    return m_status;
}

void LocationInformationReport::setStatus(const StatusFlags& newStatus)
{
    m_status = newStatus;
}

uint32_t LocationInformationReport::latitude() const
{
    return m_latitude;
}

void LocationInformationReport::setLatitude(uint32_t newLatitude)
{
    m_latitude = newLatitude;
}

uint32_t LocationInformationReport::longitude() const
{
    return m_longitude;
}

void LocationInformationReport::setLongitude(uint32_t newLongitude)
{
    m_longitude = newLongitude;
}

uint16_t LocationInformationReport::altitude() const
{
    return m_altitude;
}

void LocationInformationReport::setAltitude(uint16_t newAltitude)
{
    m_altitude = newAltitude;
}

uint16_t LocationInformationReport::speed() const
{
    return m_speed;
}

void LocationInformationReport::setSpeed(uint16_t newSpeed)
{
    m_speed = newSpeed;
}

uint16_t LocationInformationReport::bearing() const
{
    return m_bearing;
}

void LocationInformationReport::setBearing(uint16_t newBearing)
{
    m_bearing = newBearing;
}

std::string LocationInformationReport::time() const
{
    return m_time;
}

void LocationInformationReport::setTime(const std::string& newTime)
{
    m_time = newTime;
}

ExtraInfo LocationInformationReport::extra() const
{
    return m_extra;
}

void LocationInformationReport::setExtra(const ExtraInfo& newExtra)
{
    m_extra = newExtra;
}

}
