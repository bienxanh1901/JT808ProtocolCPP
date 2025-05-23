#include "JT808/MessageBody/InformationServiceMenuSetting.h"

namespace JT808::MessageBody {

InformationServiceMenuSetting::InformationServiceMenuSetting(AreaSettingType type, const std::vector<MenuItem>& menus)
    : MessageBodyBase()
    , m_type(type)
    , m_length(menus.size())
    , m_menus(menus)
{
}

void InformationServiceMenuSetting::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void InformationServiceMenuSetting::parse(const uint8_t* data, int size)
{
    int pos = 0;
    MenuItem item = {0};
    m_type = AreaSettingType(data[pos++]);

    m_length = data[pos++];

    for (int i = 0; i < m_length; i++) {
        item.type = data[pos++];
        item.length = Utils::endianSwap16(data + pos);
        pos += sizeof(item.length);
        item.info = Utils::gbkDecode(data + pos, item.length);
        pos += item.length;
        m_menus.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> InformationServiceMenuSetting::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);
    result.push_back(m_length);

    for (auto& item : m_menus) {
        result.push_back(item.type);
        Utils::appendU16(item.length, result);
        Utils::appendGBK(item.info, result);
    }

    return result;
}

bool InformationServiceMenuSetting::operator==(const InformationServiceMenuSetting& other)
{
    bool result = m_type == other.m_type && m_length == other.m_length;
    if (result && m_length > 0) {
        for (int i = 0; i < m_length; i++) {
            if (!(m_menus[i] == other.m_menus[i])) {
                return false;
            }
        }
    }

    return true;
}

InformationServiceMenuSetting::AreaSettingType InformationServiceMenuSetting::type() const
{
    return m_type;
}

void InformationServiceMenuSetting::setType(AreaSettingType newType)
{
    m_type = newType;
}

uint8_t InformationServiceMenuSetting::length() const
{
    return m_length;
}

void InformationServiceMenuSetting::setLength(uint8_t newLength)
{
    m_length = newLength;
}

std::vector<InformationServiceMenuSetting::MenuItem> InformationServiceMenuSetting::menus() const
{
    return m_menus;
}

void InformationServiceMenuSetting::setMenus(const std::vector<MenuItem>& newMenus)
{
    m_menus = newMenus;
}

}
