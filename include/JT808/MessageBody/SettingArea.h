#ifndef SETTINGAREA_H
#define SETTINGAREA_H

#include "AreaSettingProperties.h"
#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class SettingArea : public MessageBodyBase
{
public:
    SettingArea(AreaType areaType = CircularArea);
    SettingArea(AreaType areaType, AreaSettingType type, const std::vector<AreaItem>& areas);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const SettingArea& other);

    AreaSettingType type() const;
    void setType(AreaSettingType newType);
    uint8_t length() const;
    void setLength(uint8_t newLength);
    std::vector<AreaItem> areas() const;
    void setAreas(const std::vector<AreaItem>& newAreas);

private:
    AreaType m_areaType = CircularArea;
    AreaSettingType m_type = UpgradeArea;
    uint8_t m_length = 0;
    std::vector<AreaItem> m_areas;
};

}
#endif // SETTINGAREA_H
