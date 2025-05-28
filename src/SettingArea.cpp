#include "JT808/MessageBody/SettingArea.h"

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
    int pos1 = 0;
    uint8_t length = 0;

    m_type = AreaSettingType(data[pos++]);
    length = data[pos++];

    for (int i = 0; i < length; i++) {
        AreaItem item = {0};
        pos1 = item.parse(m_areaType, data + pos, size);
        pos += pos1;
        m_areas.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> SettingArea::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);
    result.push_back(m_areas.size());

    for (auto& item : m_areas) {
        Utils::append(item.package(m_areaType), result);
    }

    return result;
}

bool SettingArea::operator==(const SettingArea& other) const
{
    return m_type == other.m_type && m_areas == other.m_areas;
}

AreaSettingType SettingArea::type() const
{
    return m_type;
}

void SettingArea::setType(AreaSettingType newType)
{
    m_type = newType;
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
