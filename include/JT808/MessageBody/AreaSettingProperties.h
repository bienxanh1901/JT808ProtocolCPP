#ifndef AREASETTINGPROPERTIES_H
#define AREASETTINGPROPERTIES_H

#include <cstdint>
#include <string>

namespace JT808::MessageBody {

enum AreaType
{
    CircularArea,
    RectangularArea,
    PolygonArea
};

enum AreaSettingType
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
        uint16_t sideLat : 1; // South or North
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
    // for Circular Area
    uint32_t centerLat = 0;
    uint32_t centerLng = 0;
    uint32_t radius = 0;
    // For Rectangular Area
    uint32_t ltLat = 0;
    uint32_t ltLng = 0;
    uint32_t rbLat = 0;
    uint32_t rbLng = 0;
    std::string startTime;
    std::string endTime;
    uint16_t maxSpeed = 0;
    uint8_t overspeedDuration = 0;

    bool operator==(const AreaItem& other) const
    {
        return id == other.id && flag.value == other.flag.value && centerLat == other.centerLat
            && centerLng == other.centerLng && radius == other.radius && ltLat == other.ltLat && ltLng == other.ltLng
            && rbLat == other.rbLat && rbLng == other.rbLng && startTime == other.startTime && endTime == other.endTime
            && maxSpeed == other.maxSpeed && overspeedDuration == other.overspeedDuration;
    }
};
}

#endif // AREASETTINGPROPERTIES_H
