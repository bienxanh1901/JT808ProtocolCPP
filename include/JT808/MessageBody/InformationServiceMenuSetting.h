#ifndef INFORMATIONSERVICEMENUSETTING_H
#define INFORMATIONSERVICEMENUSETTING_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

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
        ByteArray package() const;
        void fromJson(const Json& data);
        Json toJson();
    };

    InformationServiceMenuSetting();
    InformationServiceMenuSetting(AreaSettingType type, const std::vector<MenuItem>& menus);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const InformationServiceMenuSetting& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

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
