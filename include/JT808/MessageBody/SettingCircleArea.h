#ifndef SETTINGCIRCLEAREA_H
#define SETTINGCIRCLEAREA_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class SettingCircleArea : public MessageBodyBase
{
public:
    enum SettingType
    {
        UpgradeArea = 0,
        AppendArea,
        ModifyArea
    };

    union AreaProperties {
        struct
        {
            uint16_t areaTime : 1;
            uint16_t speedLimit : 1;
            uint16_t driverAlertEnter : 1;
            uint16_t platformAlertEnter : 1;
            uint16_t driverAlertExit : 1;
            uint16_t platformAlertExit : 1;
            uint16_t sideLat : 1; // North or South
            uint16_t sideLng : 1; // East or West
            uint16_t openDoorPrevilege : 1;
            uint16_t reserved : 5;
            uint16_t commAction : 1;
            uint16_t gnssAction : 1;
        } bits;
        uint16_t value;
    };

    struct AreaItem
    {
        uint32_t id = 0;
        AreaProperties flag = {0};
        uint32_t centerLat = 0;
        uint32_t centerLng = 0;
        uint32_t radius = 0;
        std::string startTime;
        std::string endTime;
        uint16_t maxSpeed = 0;
        uint8_t overspeedDuration = 0;

        bool operator==(const AreaItem& other)
        {
            return id == other.id && flag.value == other.flag.value && centerLat == other.centerLat
                && centerLng == other.centerLng && radius == other.radius && startTime == other.startTime
                && endTime == other.endTime && maxSpeed == other.maxSpeed
                && overspeedDuration == other.overspeedDuration;
        }
    };

    SettingCircleArea() = default;
    SettingCircleArea(SettingType type, const std::vector<AreaItem>& areas);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const SettingCircleArea& other);

    SettingType type() const;
    void setType(SettingType newType);
    uint8_t length() const;
    void setLength(uint8_t newLength);
    std::vector<AreaItem> areas() const;
    void setAreas(const std::vector<AreaItem>& newAreas);

private:
    SettingType m_type = UpgradeArea;
    uint8_t m_length = 0;
    std::vector<AreaItem> m_areas;
};

}
#endif // SETTINGCIRCLEAREA_H
