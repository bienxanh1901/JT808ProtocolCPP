#ifndef EXTRALOCATIONINFORMATION_H
#define EXTRALOCATIONINFORMATION_H

#include "JT808/Common.h"
#include "LocationInformationCommon.h"
#include <cstdint>
#include <map>

namespace JT808::MessageBody {
class ExtraLocationInformation
{

public:
    ExtraLocationInformation();
    bool operator==(const ExtraLocationInformation& other) const;
    int parse(const uint8_t* data, int size);
    ByteArray package();

    void fromJson(const Json& data);
    Json toJson();

private:
    uint32_t m_mileage = 0;
    uint16_t m_fuelMeter = 0;
    uint16_t m_speed = 0;
    uint16_t m_alarmId = 0;
    OverspeedAlarm m_overspeedAlarm;
    InOutAlarm m_inOutAlarm;
    PathTimeAlarm m_pathTimeAlarm;
    ExtendedVehicleSignalFlags m_extendedSignal = {0};
    IOStatusFlags m_ioStatus = {0};
    AnalogFlag m_analog = {0};
    uint8_t m_rssi = 0;
    uint8_t m_gnssSatNum = 0;
    uint16_t m_customLength = 0;

    std::map<uint8_t, ByteArray> m_custom;

    std::map<uint8_t, uint8_t> m_ids = {
        {MileageExtraId, 0},         {FuelMeterExtraId, 0},  {SpeedExtraId, 0},         {ManualAlarmConfirmationId, 0},
        {OverspeedAlarmExtraId, 0},  {InOutAlarmExtraId, 0}, {PathTimeAlarmExtraId, 0}, {VehicleSignalStatusExtraId, 0},
        {IOStatusExtraId, 0},        {AnalogExtraId, 0},     {WirelessRSSIExtraId, 0},  {GNSSSatelliteNumberExtraId, 0},
        {CustomInfoLengthExtraId, 0}};
};

}
#endif // EXTRALOCATIONINFORMATION_H
