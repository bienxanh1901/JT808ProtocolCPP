#ifndef SETTINGAREA_H
#define SETTINGAREA_H

#include "AreaSettingProperties.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class SettingArea : public MessageBodyBase
{
public:
    SettingArea(AreaType areaType = CircularArea);
    SettingArea(AreaType areaType, AreaSettingType type, const std::vector<AreaItem>& areas);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const SettingArea& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    AreaSettingType type() const;
    void setType(AreaSettingType newType);
    std::vector<AreaItem> areas() const;
    void setAreas(const std::vector<AreaItem>& newAreas);

private:
    AreaType m_areaType = CircularArea;
    AreaSettingType m_type = UpgradeArea;
    std::vector<AreaItem> m_areas;
};

}
#endif // SETTINGAREA_H
