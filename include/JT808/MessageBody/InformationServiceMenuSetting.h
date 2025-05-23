#ifndef INFORMATIONSERVICEMENUSETTING_H
#define INFORMATIONSERVICEMENUSETTING_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class InformationServiceMenuSetting : public MessageBodyBase
{
public:
    enum SettingType
    {
        DeleteAllItem = 0,
        UpgradeMenu,
        AppendMenu,
        ModifyMenu
    };

    struct MenuItem
    {
        uint8_t type;
        uint16_t length;
        std::string info;

        bool operator==(const MenuItem& other)
        {
            return type == other.type && length == other.length && info == other.info;
        }
    };

    InformationServiceMenuSetting() = default;
    InformationServiceMenuSetting(SettingType type, const std::vector<MenuItem>& menus);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const InformationServiceMenuSetting& other);

    SettingType type() const;
    void setType(SettingType newType);
    uint8_t length() const;
    void setLength(uint8_t newLength);
    std::vector<MenuItem> menus() const;
    void setMenus(const std::vector<MenuItem>& newMenus);

private:
    SettingType m_type = DeleteAllItem;
    uint8_t m_length = 0;
    std::vector<MenuItem> m_menus;
};

}
#endif // INFORMATIONSERVICEMENUSETTING_H
