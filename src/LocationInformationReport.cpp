#include "JT808/MessageBody/LocationInformationReport.h"
#include "JT808/BCD.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {

LocationInformationReport::LocationInformationReport(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

LocationInformationReport::LocationInformationReport(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void LocationInformationReport::parse()
{

    uint8_t* data = m_rawData.data();
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

    std::vector<uint8_t> time(data + pos, data + pos + 6);
    m_time = BCD::toString(time);
    pos += 6;

    if (m_rawData.size() > pos) {
        // parse extra
        uint8_t id = 0;
        uint8_t len = 0;
        std::vector<uint8_t> value;

        while (pos <= m_rawData.size() - 2) {
            id = data[pos++];
            len = data[pos++];
            if (pos > m_rawData.size()) {
                break;
            }

            value.assign(data + pos, data + pos + len);
            pos += len;
            m_extra[id] = value;
        }
    }

    m_isValid = true;
}

void LocationInformationReport::package()
{
    Utils::U16Array u16Data = {0};
    Utils::U32Array u32Data = {0};

    m_rawData.clear();

    u32Data.value = Utils::endianSwap32(m_alarm.value);
    m_rawData.insert(m_rawData.end(), u32Data.array, u32Data.array + sizeof(u32Data));

    u32Data.value = Utils::endianSwap32(m_status.value);
    m_rawData.insert(m_rawData.end(), u32Data.array, u32Data.array + sizeof(u32Data));

    u32Data.value = Utils::endianSwap32(m_latitude);
    m_rawData.insert(m_rawData.end(), u32Data.array, u32Data.array + sizeof(u32Data));

    u32Data.value = Utils::endianSwap32(m_longitude);
    m_rawData.insert(m_rawData.end(), u32Data.array, u32Data.array + sizeof(u32Data));

    u16Data.value = Utils::endianSwap16(m_altitude);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    u16Data.value = Utils::endianSwap16(m_speed);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    u16Data.value = Utils::endianSwap16(m_bearing);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    std::vector<uint8_t> time = BCD::fromString(m_time);
    m_rawData.insert(m_rawData.end(), time.begin(), time.end());

    if (!m_extra.empty()) {
        std::vector<uint8_t> extraCustom;

        for (auto& item : m_extra) {
            if (item.first <= CustomInfoLengthExtraId) {
                m_rawData.push_back(item.first);
                if (item.first == CustomInfoLengthExtraId)
                    continue;
                m_rawData.push_back(item.second.size());
                m_rawData.insert(m_rawData.end(), item.second.begin(), item.second.end());
            } else if (item.first > CustomInfoLengthExtraId) {
                extraCustom.push_back(item.first);
                if (!item.second.empty()) {
                    extraCustom.push_back(item.second.size());
                    extraCustom.insert(extraCustom.end(), item.second.begin(), item.second.end());
                }
            }
        }

        int len = extraCustom.size();

        if (len >= 256) {
            m_rawData.push_back(2);
            m_rawData.push_back(len % 65536 / 256);
            m_rawData.push_back(len % 256);
        } else if (len > 0) {
            m_rawData.push_back(1);
            m_rawData.push_back(len % 256);
        } else {
            m_rawData.pop_back();
        }

        m_rawData.insert(m_rawData.end(), extraCustom.begin(), extraCustom.end());
    }

    m_isValid = true;
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
}
