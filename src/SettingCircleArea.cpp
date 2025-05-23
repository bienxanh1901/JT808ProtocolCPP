#include "JT808/MessageBody/SettingCircleArea.h"
#include "JT808/BCD.h"

namespace JT808::MessageBody {

SettingCircleArea::SettingCircleArea(SettingType type, const std::vector<AreaItem>& areas)
    : MessageBodyBase()
    , m_type(type)
    , m_length(areas.size())
    , m_areas(areas)
{
}

void SettingCircleArea::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void SettingCircleArea::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_type = SettingType(data[pos++]);
    m_length = data[pos++];

    for (int i = 0; i < m_length; i++) {
        AreaItem item = {0};
        item.id = Utils::endianSwap32(data + pos);
        pos += sizeof(item.id);
        item.flag.value = Utils::endianSwap16(data + pos);
        pos += sizeof(item.flag);
        item.centerLat = Utils::endianSwap32(data + pos);
        pos += sizeof(item.centerLat);
        item.centerLng = Utils::endianSwap32(data + pos);
        pos += sizeof(item.centerLng);
        item.radius = Utils::endianSwap32(data + pos);
        pos += sizeof(item.radius);

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

std::vector<uint8_t> SettingCircleArea::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);
    result.push_back(m_length);

    for (auto& item : m_areas) {
        Utils::appendU32(item.id, result);
        Utils::appendU16(item.flag.value, result);
        Utils::appendU32(item.centerLat, result);
        Utils::appendU32(item.centerLng, result);
        Utils::appendU32(item.radius, result);
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

bool SettingCircleArea::operator==(const SettingCircleArea& other)
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

SettingCircleArea::SettingType SettingCircleArea::type() const
{
    return m_type;
}

void SettingCircleArea::setType(SettingType newType)
{
    m_type = newType;
}

uint8_t SettingCircleArea::length() const
{
    return m_length;
}

void SettingCircleArea::setLength(uint8_t newLength)
{
    m_length = newLength;
}

std::vector<SettingCircleArea::AreaItem> SettingCircleArea::areas() const
{
    return m_areas;
}

void SettingCircleArea::setAreas(const std::vector<AreaItem>& newAreas)
{
    m_areas = newAreas;
}

}
