#ifndef TERMINALPARAMETER_H
#define TERMINALPARAMETER_H

#include <cstdint>
#include <map>
#include <vector>

namespace JT808::MessageBody {

using TerminalParameters = std::map<uint32_t, std::vector<uint8_t>>;

#define TOTAL_PARAMETERS 90
#define MAX_STRING_VALUE_LEN 32

/**
 * @brief TerminalParameterIds
 */
enum
{
    HeartBeatInterval = 0x0001,
    TCPMsgResponseTimeout = 0x0002,
    TCPMsgRetransmissTime = 0x0003,
    UDPMsgResponseTimeout = 0x0004,
    UDPMsgRetransmissTime = 0x0005,
    SMSMsgResponseTimeout = 0x0006,
    SMSMsgRetransmissTime = 0x0007,
    // 0x0008 - 0x000F are reserved
    MainServerAPN = 0x0010,
    MainServerUserName = 0x0011,
    MainServerPassword = 0x0012,
    MainServerAddress = 0x0013,
    BackupServerAPN = 0x0014,
    BackupServerUserName = 0x0015,
    BackupServerPassword = 0x0016,
    BackupServerAddress = 0x0017,
    ServerTCPPort = 0x0018,
    ServerUDPPort = 0x0019,
    RoadTransportCertificateICCardAuthenticationMainServerAddress = 0x001A,
    RoadTransportCertificateICCardAuthenticationMainServerTCPPort = 0x001B,
    RoadTransportCertificateICCardAuthenticationMainServerUDPPort = 0x001C,
    RoadTransportCertificateICCardAuthenticationBackupServerAddress = 0x001D,
    // 0x001E - 0x001F are reserved
    LocationReportStrategy = 0x0020,
    LocationReportMethod = 0x0021,
    DriverNotLoginReportTimeInterval = 0x0022,
    // 0x0023 - 0x0026 are reserved
    SleepingModeReportTimeInterval = 0x0027,
    EmergencyModeReportTimeInterval = 0x0028,
    DefautReportTimeInterval = 0x0029,
    // 0x002A - 0x002B are reserved
    DefautReportDistanceInterval = 0x002C,
    DriverNotLoginReportDistanceInterval = 0x002D,
    SleepingModeReportDistanceInterval = 0x002E,
    EmergencyModeReportDistanceInterval = 0x002F,
    TurningAngle = 0x0030,
    GeofenceRadius = 0x0031,
    // 0x0032 - 0x003F are reserved
    MonitorPlatformPhoneNumber = 0x0040,
    TerminalResetPhoneNumber = 0x0041,
    FactoryResetPhoneNumber = 0x0042,
    MonitorPlatformSMSNumber = 0x0043,
    TerminalSMSTextAlarmReceivedNumber = 0x0044,
    PhoneNumberAnsweringStrategy = 0x0045,
    LongestCallingDurationPerTime = 0x0046,
    LongestCallingDurationPerMonth = 0x0047,
    MonitorPhoneNumber = 0x0048,
    PlatformAdminSMSNumber = 0x0049,
    // 0x004A - 0x004F are reserved
    AlarmFlag = 0x0050,
    AlarmSMSSendingFlag = 0x0051,
    AlarmShootingFlag = 0x0052,
    AlarmShootingStorageFlag = 0x0053,
    KeyFlag = 0x0054,
    HighestSpeed = 0x0055,
    OverSpeedDuration = 0x0056,
    ContinuousDrivingTimeLimit = 0x0057,
    AccumulatedDrivingTimePerDayLimit = 0x0058,
    MinimumParkingTime = 0x0059,
    MaximumParkingTime = 0x005A,
    OverSpeedAlarmDiff = 0x005B,
    FatigueDrivingAlarmDiff = 0x005C,
    CollisionAlarmParameters = 0x005D,
    RolloverAlarmParameter = 0x005E,
    // 0x005F - 0x0063 are reserved
    TimingShootingControl = 0x0064,
    CertainDistanceShootingControl = 0x0065,
    // 0x0066 - 0x006F are reserved
    ImageQuality = 0x0070,
    ImageBrightness = 0x0071,
    ImageConstrast = 0x0072,
    ImageSaturability = 0x0073,
    ImageChromaticity = 0x0074,
    // 0x0075 - 0x007F are reserved
    VehicleOdometerReading = 0x0080,
    VehicleProvinceId = 0x0081,
    VehicleCityId = 0x0082,
    VehicleLicensePlateNumber = 0x0083,
    VehicleLicensePlateColor = 0x0084,
    // 0x0085 - 0x008F are reserved
    GNSSPositioningMode = 0x0090,
    GNSSBaudrate = 0x0091,
    GNSSOutputFrequence = 0x0092,
    GNSSOutputCollectedFrequence = 0x0093,
    GNSSDataUploadMode = 0x0094,
    GNSSUploadSetting = 0x095,
    // 0x0096 - 0x009F are reserved
    CANBusChan1CollectInterval = 0x0100,
    CANBusChan1UploadInterval = 0x0101,
    CANBusChan2CollectInterval = 0x0102,
    CANBusChan2UploadInterval = 0x0103,
    // 0x0104 - 0x010F are reserved
    CANBusIDSetting = 0x0110,
    // 0x0111 - 0x01FF other CAN Bus Id setting
    // 0xF000 - 0xFFFF User defined
} ParameterIds;

/**
 * @brief LocationReportStrategies
 */
enum
{
    RegularReportStrategy = 0x00,
    DistanceReportStrategy = 0x01,
    HybridReportStrategy = 0x02,
} LocationReportStrategies;

/**
 * @brief LocationReportingMethods
 */
enum
{
    ACCBasedMethod = 0x00,
    Login_ACCBasedMethod = 0x01,
} LocationReportingMethods;

/**
 * @brief PhoneAnswerStrategies
 */
enum
{
    AutomaticallyAnswer = 0,
    ACCOnAutomaticallyAnswer = 1, // Manually while ACC is OFF
} PhoneNumberAnswerStrategies;

/**
 * @brief GNSSBaudrates
 */
enum
{
    GNSSBRT4800 = 0x00,
    GNSSBRT9600 = 0x01,
    GNSSBRT19200 = 0x02,
    GNSSBRT38400 = 0x03,
    GNSSBRT57600 = 0x04,
    GNSSBRT115200 = 0x05,
} GNSSBaudrates;

/**
 * @brief GNSSOutputFrequences
 */
enum
{
    GNSSFreq500ms = 0x00,
    GNSSFreq1000ms = 0x01,
    GNSSFreq2000ms = 0x02,
    GNSSFreq3000ms = 0x03,
    GNSSFreq4000ms = 0x04,
} GNSSOutputFrequences;

/**
 * @brief GNSSDataUploadModes
 */
enum
{
    LocalStorageMode = 0x00,
    TimeIntervalMode = 0x01,
    DistanceIntervalMode = 0x02,
    AccumulativeTimeMode = 0x0B,
    AccumulativeDistanceMode = 0x0C,
    AccumulateiveNumberData = 0x0D,
} GNSSDataUploadModes;

/**
 * @brief CollisionAlertParam
 */
union {
    uint8_t time;
    uint8_t acceleration;
} CollisionAlertParam;

}

#endif // TERMINALPARAMETER_H
