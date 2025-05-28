#include "JT808/MessageBody/LocationInformation.h"
#include "JT808/BCD.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

LocationInformation::LocationInformation(const AlarmFlags& alarm, const StatusFlags& status, uint32_t lat, uint32_t lng,
                                         uint16_t alt, uint16_t speed, uint16_t bearing, const std::string& time,
                                         const ExtraInfo& extra)
    : alarm(alarm)
    , status(status)
    , lat(lat)
    , lng(lng)
    , alt(alt)
    , speed(speed)
    , bearing(bearing)
    , time(time)
    , extra(extra)
{
}

bool LocationInformation::operator==(const LocationInformation& other) const
{
    return alarm.value == other.alarm.value && status.value == other.status.value && lat == other.lat
        && lng == other.lng && alt == other.alt && speed == other.speed && bearing == other.bearing
        && time == other.time && extra == other.extra;
}

int LocationInformation::parse(const uint8_t* data, int size)
{

    int pos = 0;
    uint8_t id = 0;
    uint8_t len = 0;
    std::vector<uint8_t> value;

    // alarm
    alarm.value = Utils::endianSwap32(data + pos);
    pos += sizeof(alarm);
    // status
    status.value = Utils::endianSwap32(data + pos);
    pos += sizeof(status);
    // latitude
    lat = Utils::endianSwap32(data + pos);
    pos += sizeof(lat);
    // longitude
    lng = Utils::endianSwap32(data + pos);
    pos += sizeof(lng);
    // altitude
    alt = Utils::endianSwap16(data + pos);
    pos += sizeof(alt);
    // speed
    speed = Utils::endianSwap16(data + pos);
    pos += sizeof(speed);
    // bearing
    bearing = Utils::endianSwap16(data + pos);
    pos += sizeof(bearing);
    // time
    time = BCD::toString(data + pos, 6);
    pos += 6;

    // extra
    if (size > pos) {
        // parse extra
        while (pos <= size - 2) {
            id = data[pos++];
            len = data[pos++];
            if (pos > size) {
                break;
            }

            value.assign(data + pos, data + pos + len);
            pos += len;
            extra[id] = value;
        }
    }

    return pos > size ? size : pos;
}

std::vector<uint8_t> LocationInformation::package()
{
    std::vector<uint8_t> result;

    // alarm
    Utils::appendU32(alarm.value, result);
    // status
    Utils::appendU32(status.value, result);
    // lat
    Utils::appendU32(lat, result);
    // lng
    Utils::appendU32(lng, result);
    // alt
    Utils::appendU16(alt, result);
    // speed
    Utils::appendU16(speed, result);
    // bearing
    Utils::appendU16(bearing, result);
    // time
    Utils::appendBCD(time, result);
    // extra
    if (!extra.empty()) {
        std::vector<uint8_t> extraCustom;

        for (auto& item : extra) {
            if (item.first <= CustomInfoLengthExtraId) {
                result.push_back(item.first);
                if (item.first == CustomInfoLengthExtraId)
                    continue;
                result.push_back(item.second.size());
                Utils::append(item.second, result);
            } else if (item.first > CustomInfoLengthExtraId) {
                extraCustom.push_back(item.first);
                if (!item.second.empty()) {
                    extraCustom.push_back(item.second.size());
                    Utils::append(item.second, extraCustom);
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

        Utils::append(extraCustom, result);
    }

    return result;
}

}
