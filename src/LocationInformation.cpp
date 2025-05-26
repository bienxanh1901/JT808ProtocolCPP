#include "JT808/MessageBody/LocationInformation.h"
#include "JT808/BCD.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

void LocationInformation::parse(const uint8_t* data, int size)
{

    int pos = 0;

    alarm.value = Utils::endianSwap32(data + pos);
    pos += sizeof(alarm);

    status.value = Utils::endianSwap32(data + pos);
    pos += sizeof(status);

    lat = Utils::endianSwap32(data + pos);
    pos += sizeof(lat);

    lng = Utils::endianSwap32(data + pos);
    pos += sizeof(lng);

    alt = Utils::endianSwap16(data + pos);
    pos += sizeof(alt);

    speed = Utils::endianSwap16(data + pos);
    pos += sizeof(speed);

    bearing = Utils::endianSwap16(data + pos);
    pos += sizeof(bearing);

    time = BCD::toString(data + pos, 6);
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
            extra[id] = value;
        }
    }
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

}
