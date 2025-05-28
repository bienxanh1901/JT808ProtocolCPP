#ifndef LOCATIONINFORMATION_H
#define LOCATIONINFORMATION_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace JT808::MessageBody {

using ExtraInfo = std::map<uint8_t, std::vector<uint8_t>>;

/**
 * @brief LocationAdditionalInformationIds
 */
enum LocationExtraIds : uint8_t
{
    MileageExtraId = 0x01,
    FuelMeterExtraId = 0x01,
    DrivingRecordSpeedExtraId = 0x02,
    AlarmCountExtraId = 0x03,
    ManualAlarmConfirmationId = 0x04,
    // 0x05 - 0x10 are reserved
    OverSpeedAlarmExtraId = 0x11,
    InOutAlarmExtraId = 0x12,
    RouteDrivingTimeAlarmExtraId = 0x13,
    // 0x14 - 0x24 are reserved
    VehicleSignalStatusExtraId = 0x25,
    IOStatusExtraId = 0x2A,
    AnalogExtraId = 0x2B,
    WirelessRSSIExtraId = 0x30,
    GNSSSatelliteNumberExtraId = 0x31,
    CustomInfoLengthExtraId = 0xE0,
    PositioningStatusExtraId = 0xEE,
};

/**
 * @brief LocationTypes
 */
enum LocationTypes : uint8_t
{
    UnknownLocationType = 0,
    CirclularAreaLocationType = 1,
    RectangularAreaLocationType = 2,
    PolygonAreaLocationType = 3,
    RouteLocationType = 4
};

/**
 * @brief InOutAreaDirectionTypes
 */
enum InOutAreaDirectionTypes : uint8_t
{
    InAreaDirectionType = 0,
    OutAreaDirectionType = 1
};

/**
 * @brief AlarmFlags
 */
union AlarmFlags {
    struct
    {
        uint32_t sos : 1;
        uint32_t overSpeed : 1;
        uint32_t fatigueDriving : 1;
        uint32_t dangerAlert : 1;
        uint32_t gnssFault : 1;
        uint32_t gnssAntennaOpenCicuited : 1;
        uint32_t gnssAntennaShortCircuited : 1;
        uint32_t mainPowerUnderVoltage : 1;
        uint32_t mainPowerFault : 1;
        uint32_t lcdFault : 1;
        uint32_t ttsFault : 1;
        uint32_t cameraFault : 1;
        uint32_t icCardReaderFault : 1;
        uint32_t overSpeedWarning : 1;
        uint32_t fatigueDrivingWarning : 1;
        uint32_t reserved : 3;
        uint32_t dayDrivingOvertime : 1;
        uint32_t parkingOvertime : 1;
        uint32_t inOutArea : 1;
        uint32_t inOutRoute : 1;
        uint32_t routeDrivingTime : 1;
        uint32_t offTrack : 1;
        uint32_t vssFault : 1;
        uint32_t fuelFault : 1;
        uint32_t stolen : 1;
        uint32_t acc : 1;
        uint32_t move : 1;
        uint32_t collision : 1;
        uint32_t rollover : 1;
        uint32_t doorOpen : 1;
    } bits;
    uint32_t value = 0;
};

/**
 * @brief StatusFlags
 */
union StatusFlags {
    struct
    {
        uint32_t isAccOn : 1;
        uint32_t isPositioning : 1;
        uint32_t SNLat : 1;
        uint32_t EWLng : 1;
        uint32_t isStoped : 1;
        uint32_t isLocationEncrypted : 1;
        uint32_t reserved : 2;
        uint32_t loadStatus : 2;
        uint32_t isFuelCut : 1;
        uint32_t isFircuitCut : 1;
        uint32_t isDoorLocked : 1;
        uint32_t isFrontDoorOpen : 1;
        uint32_t isMiddleDoorOpen : 1;
        uint32_t isBackDoorOpen : 1;
        uint32_t isDriverDoorOpen : 1;
        uint32_t isOtherDoorOpen : 1;
        uint32_t isGPS : 1;
        uint32_t isBDS : 1;
        uint32_t isGLONASS : 1;
        uint32_t isGalileo : 1;
        uint32_t reserved2 : 10;
    } bits;
    uint32_t value = 0;
};

/**
 * @brief ExtendedVehicleSignalFlags
 */
union ExtendedVehicleSignalFlags {
    struct
    {
        uint32_t lowBeam : 1;
        uint32_t highBeam : 1;
        uint32_t righTurn : 1;
        uint32_t leftTurn : 1;
        uint32_t brake : 1;
        uint32_t reverse : 1;
        uint32_t fog : 2;
        uint32_t sideMarker : 2;
        uint32_t horn : 1;
        uint32_t airConditioner : 1;
        uint32_t neutral : 1;
        uint32_t retarder : 1;
        uint32_t abs : 1;
        uint32_t heater : 1;
        uint32_t cluth : 1;
        uint32_t reserved : 17;
    } bits;
    uint32_t value = 0;
};

/**
 * @brief IOStatusFlags
 */
union IOStatusFlags {
    struct
    {
        uint16_t deepSleep : 1;
        uint16_t sleep : 1;
        uint16_t reserved : 14;
    } bits;
    uint16_t value = 0;
};

struct LocationInformation
{
    AlarmFlags alarm = {0};
    StatusFlags status = {0};
    uint32_t lat = 0;
    uint32_t lng = 0;
    uint16_t alt = 0;
    uint16_t speed = 0;
    uint16_t bearing = 0;
    std::string time;
    ExtraInfo extra;

    LocationInformation() = default;
    LocationInformation(const AlarmFlags& alarm, const StatusFlags& status, uint32_t lat, uint32_t lng, uint16_t alt,
                        uint16_t speed, uint16_t bearing, std::string time, ExtraInfo extra = {});
    bool operator==(const LocationInformation& other) const;
    int parse(const uint8_t* data, int size);
    std::vector<uint8_t> package();
};

}
#endif // LOCATIONINFORMATION_H
