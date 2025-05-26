#include "JT808/MessageBody/SettingArea.h"
#include "JT808/BCD.h"

namespace JT808::MessageBody {

SettingArea::SettingArea(AreaType areaType)
    : MessageBodyBase()
    , m_areaType(areaType)
{
}

SettingArea::SettingArea(AreaType areaType, AreaSettingType type, const std::vector<AreaItem>& areas)
    : MessageBodyBase()
    , m_areaType(areaType)
    , m_type(type)
    , m_length(areas.size())
    , m_areas(areas)
{
}

void SettingArea::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void SettingArea::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_type = AreaSettingType(data[pos++]);
    m_length = data[pos++];

    for (int i = 0; i < m_length; i++) {
        AreaItem item = {0};
        item.id = Utils::endianSwap32(data + pos);
        pos += sizeof(item.id);
        item.flag.value = Utils::endianSwap16(data + pos);
        pos += sizeof(item.flag);

        if (m_areaType == CircularArea) {
            item.centerLat = Utils::endianSwap32(data + pos);
            pos += sizeof(item.centerLat);
            item.centerLng = Utils::endianSwap32(data + pos);
            pos += sizeof(item.centerLng);
            item.radius = Utils::endianSwap32(data + pos);
            pos += sizeof(item.radius);
        } else if (m_areaType == RectangularArea) {
            item.ltLat = Utils::endianSwap32(data + pos);
            pos += sizeof(item.ltLat);
            item.ltLng = Utils::endianSwap32(data + pos);
            pos += sizeof(item.ltLng);
            item.rbLat = Utils::endianSwap32(data + pos);
            pos += sizeof(item.rbLat);
            item.rbLng = Utils::endianSwap32(data + pos);
            pos += sizeof(item.rbLng);
        }

        if (item.flag.bits.areaTime == 1) {
            item.startTime = BCD::toString(data + pos, 6);
            pos += 6;
            item.endTime = BCD::toString(data + pos, 6);
            pos += 6;
        }

        if (item.flag.bits.speedLimit == 1) {
            item.maxSpeed = Utils::endianSwap16(data + pos);
            pos += sizeof(item.maxSpeed);
            item.overspeedDuration = data[pos++];
        }

        m_areas.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> SettingArea::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);
    result.push_back(m_length);

    for (auto& item : m_areas) {
        Utils::appendU32(item.id, result);
        Utils::appendU16(item.flag.value, result);

        if (m_areaType == CircularArea) {
            Utils::appendU32(item.centerLat, result);
            Utils::appendU32(item.centerLng, result);
            Utils::appendU32(item.radius, result);
        } else if (m_areaType == RectangularArea) {
            Utils::appendU32(item.ltLat, result);
            Utils::appendU32(item.ltLng, result);
            Utils::appendU32(item.rbLat, result);
            Utils::appendU32(item.rbLng, result);
        }

        if (item.flag.bits.areaTime == 1) {
            Utils::appendBCD(item.startTime, result);
            Utils::appendBCD(item.endTime, result);
        }

        if (item.flag.bits.speedLimit == 1) {
            Utils::appendU16(item.maxSpeed, result);
            result.push_back(item.overspeedDuration);
        }
    }

    return result;
}

bool SettingArea::operator==(const SettingArea& other)
{
    bool result = m_type == other.m_type && m_length == other.m_length;
    if (result && m_length > 0) {
        for (int i = 0; i < m_length; i++) {
            if (!(m_areas[i] == other.m_areas[i])) {
                return false;
            }
        }
    }

    return true;
}

AreaSettingType SettingArea::type() const
{
    return m_type;
}

void SettingArea::setType(AreaSettingType newType)
{
    m_type = newType;
}

uint8_t SettingArea::length() const
{
    return m_length;
}

void SettingArea::setLength(uint8_t newLength)
{
    m_length = newLength;
}

std::vector<AreaItem> SettingArea::areas() const
{
    return m_areas;
}

void SettingArea::setAreas(const std::vector<AreaItem>& newAreas)
{
    m_areas = newAreas;
}

}
