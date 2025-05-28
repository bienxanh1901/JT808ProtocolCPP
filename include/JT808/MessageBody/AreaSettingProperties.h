#ifndef AREASETTINGPROPERTIES_H
#define AREASETTINGPROPERTIES_H

#include <cstdint>
#include <string>
#include <vector>

namespace JT808::MessageBody {

enum AreaType : uint8_t
{
    CircularArea = 0,
    RectangularArea,
    PolygonArea
};

enum AreaSettingType : uint8_t
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
    uint16_t value = 0;
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

    bool operator==(const AreaItem& other) const;
    int parse(AreaType type, const uint8_t* data, int size);
    std::vector<uint8_t> package(AreaType type);
};
}

#endif // AREASETTINGPROPERTIES_H
