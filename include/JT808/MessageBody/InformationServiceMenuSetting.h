#ifndef INFORMATIONSERVICEMENUSETTING_H
#define INFORMATIONSERVICEMENUSETTING_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class InformationServiceMenuSetting : public MessageBodyBase
{
public:
    enum AreaSettingType : uint8_t
    {
        DeleteAllItem = 0,
        UpgradeMenu,
        AppendMenu,
        ModifyMenu
    };

    struct MenuItem
    {
        uint8_t type = 0;
        std::string info;

        bool operator==(const MenuItem& other) const;
        int parse(const uint8_t* data, int size);
        std::vector<uint8_t> package();
    };

    InformationServiceMenuSetting() = default;
    InformationServiceMenuSetting(AreaSettingType type, const std::vector<MenuItem>& menus);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const InformationServiceMenuSetting& other) const;

    AreaSettingType type() const;
    void setType(AreaSettingType newType);
    std::vector<MenuItem> menus() const;
    void setMenus(const std::vector<MenuItem>& newMenus);

private:
    AreaSettingType m_type = DeleteAllItem;
    std::vector<MenuItem> m_menus;
};

}
#endif // INFORMATIONSERVICEMENUSETTING_H
