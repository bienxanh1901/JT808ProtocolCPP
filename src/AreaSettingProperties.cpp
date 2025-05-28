#include "JT808/MessageBody/AreaSettingProperties.h"
#include "JT808/BCD.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

bool AreaItem::operator==(const AreaItem& other) const
{
    return id == other.id && flag.value == other.flag.value && centerLat == other.centerLat
        && centerLng == other.centerLng && radius == other.radius && ltLat == other.ltLat && ltLng == other.ltLng
        && rbLat == other.rbLat && rbLng == other.rbLng && startTime == other.startTime && endTime == other.endTime
        && maxSpeed == other.maxSpeed && overspeedDuration == other.overspeedDuration;
}

int AreaItem::parse(AreaType type, const uint8_t* data, int size)
{
    int pos = 0;

    // id
    id = Utils::endianSwap32(data + pos);
    pos += sizeof(id);
    // flag
    flag.value = Utils::endianSwap16(data + pos);
    pos += sizeof(flag);

    if (type == CircularArea) {
        // centerLat
        centerLat = Utils::endianSwap32(data + pos);
        pos += sizeof(centerLat);
        // centerLng
        centerLng = Utils::endianSwap32(data + pos);
        pos += sizeof(centerLng);
        // radius
        radius = Utils::endianSwap32(data + pos);
        pos += sizeof(radius);
    } else if (type == RectangularArea) {
        // left top lat
        ltLat = Utils::endianSwap32(data + pos);
        pos += sizeof(ltLat);
        // left top lng
        ltLng = Utils::endianSwap32(data + pos);
        pos += sizeof(ltLng);
        // right bottom lat
        rbLat = Utils::endianSwap32(data + pos);
        pos += sizeof(rbLat);
        // right bottom lng
        rbLng = Utils::endianSwap32(data + pos);
        pos += sizeof(rbLng);
    }

    if (flag.bits.areaTime == 1) {
        // startTime
        startTime = BCD::toString(data + pos, 6);
        pos += 6;
        // endTime
        endTime = BCD::toString(data + pos, 6);
        pos += 6;
    }

    if (flag.bits.speedLimit == 1) {
        // maxSpeed
        maxSpeed = Utils::endianSwap16(data + pos);
        pos += sizeof(maxSpeed);
        // overspeedDuration
        overspeedDuration = data[pos];
    }

    return pos;
}

std::vector<uint8_t> AreaItem::package(AreaType type)
{
    std::vector<uint8_t> result;

    // id
    Utils::appendU32(id, result);
    // flag
    Utils::appendU16(flag.value, result);

    if (type == CircularArea) {
        // centerLat
        Utils::appendU32(centerLat, result);
        // centerLng
        Utils::appendU32(centerLng, result);
        // radius
        Utils::appendU32(radius, result);
    } else if (type == RectangularArea) {
        // left top lat
        Utils::appendU32(ltLat, result);
        // left top lng
        Utils::appendU32(ltLng, result);
        // right bottom lat
        Utils::appendU32(rbLat, result);
        // right bottom lng
        Utils::appendU32(rbLng, result);
    }

    if (flag.bits.areaTime == 1) {
        // startTime
        Utils::appendBCD(startTime, result);
        // endTime
        Utils::appendBCD(endTime, result);
    }

    if (flag.bits.speedLimit == 1) {
        // maxSpeed
        Utils::appendU16(maxSpeed, result);
        // overspeedDuration
        result.push_back(overspeedDuration);
    }

    return result;
}

}
