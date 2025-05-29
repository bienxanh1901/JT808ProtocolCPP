#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "JT808/MessageBody/LocationInformationCommon.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

ExtraLocationInformation::ExtraLocationInformation() { }

bool ExtraLocationInformation::operator==(const ExtraLocationInformation& other) const
{
    return m_mileage == other.m_mileage && m_fuelMeter == other.m_fuelMeter && m_speed == other.m_speed
        && m_alarmId == other.m_alarmId && m_overspeedAlarm == other.m_overspeedAlarm
        && m_inOutAlarm == other.m_inOutAlarm && m_pathTimeAlarm == other.m_pathTimeAlarm
        && m_extendedSignal.value == other.m_extendedSignal.value && m_ioStatus.value == other.m_ioStatus.value
        && m_analog.value == other.m_analog.value && m_rssi == other.m_rssi && m_gnssSatNum == other.m_gnssSatNum
        && m_customLength == other.m_customLength && m_custom == other.m_custom && m_ids == other.m_ids;
}

int ExtraLocationInformation::parse(const uint8_t* data, int size)
{
    int pos = 0;
    uint8_t id = 0;
    uint8_t length = 0;
    std::vector<uint8_t> value;

    while (pos <= size - 2) {
        id = data[pos++];
        length = data[pos++];
        if (pos > size) {
            break;
        }

        if (id <= CustomInfoLengthExtraId) {
            m_ids[id] = 1;
            switch (id) {
            case MileageExtraId:
                m_mileage = Utils::endianSwap32(data + pos);
                break;
            case FuelMeterExtraId:
                m_fuelMeter = Utils::endianSwap16(data + pos);
                break;
            case SpeedExtraId:
                m_speed = Utils::endianSwap16(data + pos);
                break;
            case ManualAlarmConfirmationId:
                m_alarmId = Utils::endianSwap16(data + pos);
                break;
            case OverspeedAlarmExtraId:
                m_overspeedAlarm.parse(data + pos, length);
            case InOutAlarmExtraId:
                m_inOutAlarm.parse(data + pos, length);
                break;
            case PathTimeAlarmExtraId:
                m_pathTimeAlarm.parse(data + pos, length);
                break;
            case VehicleSignalStatusExtraId:
                m_extendedSignal.value = Utils::endianSwap32(data + pos);
                break;
            case IOStatusExtraId:
                m_ioStatus.value = Utils::endianSwap16(data + pos);
                break;
            case AnalogExtraId:
                m_analog.value = Utils::endianSwap32(data + pos);
                break;
            case WirelessRSSIExtraId:
                m_rssi = data[pos];
                break;
            case GNSSSatelliteNumberExtraId:
                m_gnssSatNum = data[pos];
                break;
            case CustomInfoLengthExtraId:
                if (length == 1) {
                    m_customLength = data[pos];
                } else {
                    m_customLength = Utils::endianSwap16(data + pos);
                }
                break;
            default:
                break;
            }
        } else {
            value.assign(data + pos, data + pos + length);
            m_custom[id] = value;
        }

        pos += length;
    }

    return pos;
}

std::vector<uint8_t> ExtraLocationInformation::package()
{
    std::vector<uint8_t> result;
    for (auto& id : m_ids) {
        if (id.second == 1) {
            result.push_back(id.first);
            switch (id.first) {
            case MileageExtraId:
                result.push_back(sizeof(m_mileage));
                Utils::appendU32(m_mileage, result);
                break;
            case FuelMeterExtraId:
                result.push_back(sizeof(m_fuelMeter));
                Utils::appendU16(m_fuelMeter, result);
                break;
            case SpeedExtraId:
                result.push_back(sizeof(m_speed));
                Utils::appendU16(m_speed, result);
                break;
            case ManualAlarmConfirmationId:
                result.push_back(sizeof(m_alarmId));
                Utils::appendU16(m_alarmId, result);
                break;
            case OverspeedAlarmExtraId:
                Utils::append(m_overspeedAlarm.package(), result);
                break;
            case InOutAlarmExtraId:
                Utils::append(m_inOutAlarm.package(), result);
                break;
            case PathTimeAlarmExtraId:
                Utils::append(m_pathTimeAlarm.package(), result);
                break;
            case VehicleSignalStatusExtraId:
                result.push_back(sizeof(m_extendedSignal.value));
                Utils::appendU32(m_extendedSignal.value, result);
                break;
            case IOStatusExtraId:
                result.push_back(sizeof(m_ioStatus.value));
                Utils::appendU16(m_ioStatus.value, result);
                break;
            case AnalogExtraId:
                result.push_back(sizeof(m_analog.value));
                Utils::appendU32(m_analog.value, result);
                break;
            case WirelessRSSIExtraId:
                result.push_back(1);
                result.push_back(m_rssi);
                break;
            case GNSSSatelliteNumberExtraId:
                result.push_back(1);
                result.push_back(m_gnssSatNum);
                break;
            case CustomInfoLengthExtraId:
                if (m_customLength > 255) {
                    result.push_back(2);
                    Utils::appendU16(m_customLength, result);
                } else {
                    result.push_back(1);
                    result.push_back(m_customLength);
                }
                break;
            default:
                break;
            }
        }
    }

    if (!m_custom.empty()) {
        for (auto& item : m_custom) {
            result.push_back(item.first);
            if (!item.second.empty()) {
                result.push_back(item.second.size());
                Utils::append(item.second, result);
            }
        }
    }

    return result;
}

void ExtraLocationInformation::fromJson(const nlohmann::json& data)
{

    for (auto& id : m_ids) {
        id.second = 0;
    }

    if (data.contains("mileage")) {
        m_mileage = data["mileage"];
        m_ids[MileageExtraId] = 1;
    }

    if (data.contains("fuel_meter")) {
        m_fuelMeter = data["fuel_meter"];
        m_ids[FuelMeterExtraId] = 1;
    }

    if (data.contains("speed")) {
        m_speed = data["speed"];
        m_ids[SpeedExtraId] = 1;
    }

    if (data.contains("alarm_id")) {
        m_alarmId = data["alarm_id"];
        m_ids[ManualAlarmConfirmationId] = 1;
    }

    if (data.contains("overspeed_alarm")) {
        m_overspeedAlarm.fromJson(data["overspeed_alarm"]);
        m_ids[OverspeedAlarmExtraId] = 1;
    }

    if (data.contains("in_out_alarm")) {
        m_inOutAlarm.fromJson(data["in_out_alarm"]);
        m_ids[InOutAlarmExtraId] = 1;
    }

    if (data.contains("path_time_alarm")) {
        m_pathTimeAlarm.fromJson(data["path_time_alarm"]);
        m_ids[PathTimeAlarmExtraId] = 1;
    }

    if (data.contains("extended_vehicle_signal_status")) {
        m_extendedSignal.fromJson(data["extended_vehicle_signal_status"]);
        m_ids[VehicleSignalStatusExtraId] = 1;
    }

    if (data.contains("io_status")) {
        m_ioStatus.fromJson(data["io_status"]);
        m_ids[IOStatusExtraId] = 1;
    }

    if (data.contains("analog")) {
        m_analog.fromJson(data["analog"]);
        m_ids[AnalogExtraId] = 1;
    }

    if (data.contains("rssi")) {
        m_rssi = data["rssi"];
        m_ids[m_rssi] = 1;
    }

    if (data.contains("gnss_sat_num")) {
        m_gnssSatNum = data["gnss_sat_num"];
        m_ids[GNSSSatelliteNumberExtraId] = 1;
    }

    if (data.contains("custom")) {
        m_customLength = 0;
        for (auto& item : data["custom"]) {
            m_custom[item["id"]] = item["data"].get<std::vector<uint8_t>>();
            m_customLength += item["length"].get<int>();
        }
        m_ids[CustomInfoLengthExtraId] = 1;
    }
}

nlohmann::json ExtraLocationInformation::toJson()
{
    nlohmann::json result = nlohmann::json::object({});

    for (auto& id : m_ids) {
        if (id.second == 1) {
            switch (id.first) {
            case MileageExtraId:
                result["mileage"] = m_mileage;
                break;
            case FuelMeterExtraId:
                result["fuel_meter"] = m_fuelMeter;
                break;
            case SpeedExtraId:
                result["speed"] = m_speed;
                break;
            case ManualAlarmConfirmationId:
                result["alarm_id"] = m_alarmId;
                break;
            case OverspeedAlarmExtraId:
                result["overspeed_alarm"] = m_overspeedAlarm.toJson();
                break;
            case InOutAlarmExtraId:
                result["in_out_alarm"] = m_inOutAlarm.toJson();
                break;
            case PathTimeAlarmExtraId:
                result["path_time_alarm"] = m_pathTimeAlarm.toJson();
                break;
            case VehicleSignalStatusExtraId:
                result["extended_vehicle_signal_status"] = m_extendedSignal.toJson();
                break;
            case IOStatusExtraId:
                result["io_status"] = m_ioStatus.toJson();
                break;
            case AnalogExtraId:
                result["analog"] = m_analog.toJson();
                break;
            case WirelessRSSIExtraId:
                result["rssi"] = m_rssi;
                break;
            case GNSSSatelliteNumberExtraId:
                result["gnss_sat_num"] = m_gnssSatNum;
                break;
            case CustomInfoLengthExtraId:
            default:
                break;
            }
        }
    }

    if (!m_custom.empty()) {
        result["custom"] = nlohmann::json::array({});
        for (auto& item : m_custom) {
            result.push_back(
                nlohmann::json::object({{"id", item.first}, {"data", item.second}, {"length", item.second.size()}}));
        }
    }
    return result;
}

}
