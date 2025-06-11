#include "JT808/MessageBody/InformationServiceMenuSetting.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/InformationServiceMenuSettingSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

InformationServiceMenuSetting::InformationServiceMenuSetting()
    : MessageBodyBase(Schema::InformationServiceMenuSettingSchema)
{
}

InformationServiceMenuSetting::InformationServiceMenuSetting(AreaSettingType type, const std::vector<MenuItem>& menus)
    : MessageBodyBase(Schema::InformationServiceMenuSettingSchema)
    , m_type(type)
    , m_menus(menus)
{
}

void InformationServiceMenuSetting::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void InformationServiceMenuSetting::parse(const uint8_t* data, int size)
{
    int pos = 0;
    int pos1 = 0;
    uint8_t length = 0;

    // type
    m_type = AreaSettingType(data[pos++]);
    // length
    length = data[pos++];
    // menus
    for (int i = 0; i < length; i++) {
        MenuItem item = {0};
        pos1 = item.parse(data + pos, size);
        pos += pos1;
        m_menus.push_back(item);
    }

    setIsValid(true);
}

ByteArray InformationServiceMenuSetting::package()
{
    ByteArray result;
    // type
    result.push_back(m_type);
    // length
    result.push_back(m_menus.size());

    for (auto& item : m_menus) {
        Utils::append(item.package(), result);
    }

    return result;
}

bool InformationServiceMenuSetting::operator==(const InformationServiceMenuSetting& other) const
{
    return m_type == other.m_type && m_menus == other.m_menus;
}

void InformationServiceMenuSetting::fromJson(const Json& data)
{
    if (validate(data)) {
        m_type = AreaSettingType(data["type"]);
        if (data["length"] > 0) {
            MenuItem item = {0};
            for (auto& menu : data["menus"]) {
                item.fromJson(menu);
                m_menus.push_back(item);
            }
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json InformationServiceMenuSetting::toJson()
{
    Json result({{"type", m_type}, {"length", m_menus.size()}, {"menus", {}}});
    for (auto& item : m_menus) {
        result["menus"].push_back(item.toJson());
    }

    return result;
}

InformationServiceMenuSetting::AreaSettingType InformationServiceMenuSetting::type() const
{
    return m_type;
}

void InformationServiceMenuSetting::setType(AreaSettingType newType)
{
    m_type = newType;
}

std::vector<InformationServiceMenuSetting::MenuItem> InformationServiceMenuSetting::menus() const
{
    return m_menus;
}

void InformationServiceMenuSetting::setMenus(const std::vector<MenuItem>& newMenus)
{
    m_menus = newMenus;
}

bool InformationServiceMenuSetting::MenuItem::operator==(const MenuItem& other) const
{
    return type == other.type && info == other.info;
}

int InformationServiceMenuSetting::MenuItem::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    uint16_t length = 0;
    // type
    type = data[pos++];
    // length
    length = Utils::endianSwap16(data + pos);
    pos += sizeof(length);
    // info
    info = Utils::gbkDecode(data + pos, length);
    pos += length;

    return pos;
}

ByteArray InformationServiceMenuSetting::MenuItem::package() const
{
    ByteArray result;
    // type
    result.push_back(type);
    // length
    Utils::appendU16(info.size(), result);
    // info
    Utils::appendGBK(info, result);

    return result;
}

void InformationServiceMenuSetting::MenuItem::fromJson(const Json& data)
{
    type = data["type"];
    info = data["info"];
}

Json InformationServiceMenuSetting::MenuItem::toJson()
{
    return {{"type", type}, {"info", info}};
}

}
