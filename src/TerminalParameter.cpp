#include "JT808/MessageBody/TerminalParameter.h"
#include "JT808/Common.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <map>
#include <vector>

namespace JT808::MessageBody {

std::map<uint32_t, JT808::DataType> paramTypes = {
    {HeartBeatInterval, DWORD},
    {TCPMsgResponseTimeout, DWORD},
    {TCPMsgRetransmissTime, DWORD},
    {UDPMsgResponseTimeout, DWORD},
    {UDPMsgRetransmissTime, DWORD},
    {SMSMsgResponseTimeout, DWORD},
    {SMSMsgRetransmissTime, DWORD},
    {ServerTCPPort, DWORD},
    {ServerUDPPort, DWORD},
    {RoadTransportCertificateICCardAuthenticationMainServerTCPPort, DWORD},
    {RoadTransportCertificateICCardAuthenticationMainServerUDPPort, DWORD},
    {LocationReportStrategy, DWORD},
    {LocationReportMethod, DWORD},
    {DriverNotLoginReportTimeInterval, DWORD},
    {SleepingModeReportTimeInterval, DWORD},
    {EmergencyModeReportTimeInterval, DWORD},
    {DefautReportTimeInterval, DWORD},
    {DefautReportDistanceInterval, DWORD},
    {DriverNotLoginReportDistanceInterval, DWORD},
    {SleepingModeReportDistanceInterval, DWORD},
    {EmergencyModeReportDistanceInterval, DWORD},
    {TurningAngle, DWORD},
    {PhoneNumberAnsweringStrategy, DWORD},
    {LongestCallingDurationPerTime, DWORD},
    {LongestCallingDurationPerMonth, DWORD},
    {AlarmFlag, DWORD},
    {AlarmSMSSendingFlag, DWORD},
    {AlarmShootingFlag, DWORD},
    {AlarmShootingStorageFlag, DWORD},
    {KeyFlag, DWORD},
    {HighestSpeed, DWORD},
    {OverSpeedDuration, DWORD},
    {ContinuousDrivingTimeLimit, DWORD},
    {AccumulatedDrivingTimePerDayLimit, DWORD},
    {MinimumParkingTime, DWORD},
    {MaximumParkingTime, DWORD},
    {TimingShootingControl, DWORD},
    {CertainDistanceShootingControl, DWORD},
    {ImageQuality, DWORD},
    {ImageBrightness, DWORD},
    {ImageConstrast, DWORD},
    {ImageSaturability, DWORD},
    {ImageChromaticity, DWORD},
    {VehicleOdometerReading, DWORD},
    {GNSSOutputCollectedFrequence, DWORD},
    {GNSSUploadSetting, DWORD},
    {CANBusChan1CollectInterval, DWORD},
    {CANBusChan2CollectInterval, DWORD},
    {GeofenceRadius, WORD},
    {OverSpeedAlarmDiff, WORD},
    {FatigueDrivingAlarmDiff, WORD},
    {CollisionAlarmParameters, WORD},
    {RolloverAlarmParameter, WORD},
    {VehicleProvinceId, WORD},
    {VehicleCityId, WORD},
    {CANBusChan1UploadInterval, WORD},
    {CANBusChan2UploadInterval, WORD},
    {VehicleLicensePlateColor, BYTE},
    {GNSSPositioningMode, BYTE},
    {GNSSBaudrate, BYTE},
    {GNSSOutputFrequence, BYTE},
    {GNSSDataUploadMode, BYTE},
    {MainServerAPN, STRING},
    {MainServerUserName, STRING},
    {MainServerPassword, STRING},
    {MainServerAddress, STRING},
    {BackupServerAPN, STRING},
    {BackupServerUserName, STRING},
    {BackupServerPassword, STRING},
    {BackupServerAddress, STRING},
    {RoadTransportCertificateICCardAuthenticationMainServerAddress, STRING},
    {RoadTransportCertificateICCardAuthenticationBackupServerAddress, STRING},
    {MonitorPlatformPhoneNumber, STRING},
    {TerminalResetPhoneNumber, STRING},
    {FactoryResetPhoneNumber, STRING},
    {MonitorPlatformSMSNumber, STRING},
    {TerminalSMSTextAlarmReceivedNumber, STRING},
    {MonitorPhoneNumber, STRING},
    {PlatformAdminSMSNumber, STRING},
    {VehicleLicensePlateNumber, STRING},
    {CANBusIDSetting, BYTEARRAY}};

bool TerminalParameter::operator==(const TerminalParameter& other) const
{
    return id == other.id && num.value == other.num.value && str == other.str;
}

int MessageBody::TerminalParameter::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    int length = 0;
    id = Utils::endianSwap32(data);
    pos += sizeof(id);
    length = data[pos++];

    if (id <= CANBusIDSetting) {
        if (paramTypes.find(id) != paramTypes.end()) {
            switch (paramTypes[id]) {
            case BYTE:
                num.u8 = data[pos++];
                break;
            case WORD:
                num.u16 = Utils::endianSwap16(data + pos);
                pos += 2;
                break;
            case DWORD:
                num.u32 = Utils::endianSwap32(data + pos);
                pos += 4;
                break;
            case BYTEARRAY:
                // for can bus
                num.canSetting.collectInterval = Utils::endianSwap32(data + pos);
                pos += 4;
                num.canSetting.canId = Utils::endianSwap32(data + pos);
                pos += 4;
                break;
            case STRING:
            default:
                str.assign(data + pos, data + pos + length);
                pos += length;
                break;
            }
        } else {
            pos += length;
        }

    } else {
        other.assign(data + pos, data + pos + length);
        pos += length;
    }

    return pos;
}

std::vector<uint8_t> TerminalParameter::package()
{
    std::vector<uint8_t> result;
    Utils::appendU32(id, result);

    if (id <= CANBusIDSetting) {
        if (paramTypes.find(id) != paramTypes.end()) {
            switch (paramTypes[id]) {
            case BYTE:
                result.push_back(sizeof(num.u8));
                result.push_back(num.u8);
                break;
            case WORD:
                result.push_back(sizeof(num.u16));
                Utils::appendU16(num.u16, result);
                break;
            case DWORD:
                result.push_back(sizeof(num.u32));
                Utils::appendU32(num.u32, result);
                break;
            case BYTEARRAY:
                // for can bus
                result.push_back(sizeof(num.canSetting));
                Utils::appendU32(num.canSetting.collectInterval, result);
                Utils::appendU32(num.canSetting.canId, result);
                break;
            case STRING:
            default:
                result.push_back(str.length());
                Utils::append(str, result);
                break;
            }
        }
    } else {
        Utils::append(other, result);
    }

    return result;
}

void TerminalParameter::fromJson(const nlohmann::json& data)
{

    id = data["id"];

    if (id <= CANBusIDSetting) {
        if (paramTypes.find(id) != paramTypes.end()) {
            switch (paramTypes[id]) {
            case BYTE:
                num.u8 = data["value"];
                break;
            case WORD:
                num.u16 = data["value"];
                break;
            case DWORD:
                num.u32 = data["value"];
                break;
            case BYTEARRAY:
                // for can bus
                num.value = data["value"];
                break;
            case STRING:
            default:
                str = data["value"];
                break;
            }
        }
    } else {
        other = data["value"].get<std::vector<uint8_t>>();
    }
}

nlohmann::json TerminalParameter::toJson()
{
    nlohmann::json result = nlohmann::json::object({{"id", id}});

    if (id <= CANBusIDSetting) {
        if (paramTypes.find(id) != paramTypes.end()) {
            switch (paramTypes[id]) {
            case BYTE:
            case WORD:
            case DWORD:
            case BYTEARRAY:
                result["value"] = num.value;
                break;
            case STRING:
            default:
                result["value"] = str;
                break;
            }
        }
    } else {
        result["value"] = other;
    }

    return result;
}

}
