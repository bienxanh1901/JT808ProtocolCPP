#include "JT808/MessageBody/SettingArea.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/AreaSettingProperties.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/SettingAreaSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

SettingArea::SettingArea(AreaType areaType)
    : MessageBodyBase(areaType == CircularArea ? Schema::CircularAreaSettingSchema
                                               : Schema::RectangularAreaSettingSchema)
    , m_areaType(areaType)
{
}

SettingArea::SettingArea(AreaType areaType, AreaSettingType type, const std::vector<AreaItem>& areas)
    : MessageBodyBase(areaType == CircularArea ? Schema::CircularAreaSettingSchema
                                               : Schema::RectangularAreaSettingSchema)
    , m_areaType(areaType)
    , m_type(type)
    , m_areas(areas)
{
}

void SettingArea::parse(const ByteArray& data)
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

ByteArray SettingArea::package()
{
    ByteArray result;

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

void SettingArea::fromJson(const Json& data)
{
    if (validate(data)) {
        m_type = AreaSettingType(data["type"]);
        if (data["length"] > 0) {
            for (auto& area : data["areas"]) {
                AreaItem item = {0};
                item.fromJson(m_areaType, area);

                m_areas.push_back(item);
            }
        }

        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json SettingArea::toJson()
{
    Json result(Json::object({{"type", m_type}, {"length", m_areas.size()}, {"areas", {}}}));

    for (auto& item : m_areas) {
        result["areas"].push_back(item.toJson(m_areaType));
    }

    return result;
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
