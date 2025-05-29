#include "JT808/MessageBody/LocationInformationCommon.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

bool OverspeedAlarm::operator==(const OverspeedAlarm& other) const
{
    return type == other.type && id == other.id;
}

void OverspeedAlarm::parse(const uint8_t* data, int /*size*/)
{
    type = LocationTypes(data[0]);
    if (type > UnknownLocationType) {
        id = Utils::endianSwap32(data + 1);
    }
}

std::vector<uint8_t> OverspeedAlarm::package()
{
    std::vector<uint8_t> result;

    if (type > LocationTypes::UnknownLocationType) {
        result.push_back(5);
        result.push_back(type);
        Utils::appendU32(id, result);
    } else {
        result.push_back(1);
        result.push_back(type);
    }

    return result;
}

void OverspeedAlarm::fromJson(const nlohmann::json& data)
{
    type = data["type"];
    if (type != UnknownLocationType) {
        id = data["id"];
    }
}

nlohmann::json OverspeedAlarm::toJson()
{
    nlohmann::json result = nlohmann::json::object({{"type", type}});
    if (type != UnknownLocationType) {
        result["id"] = id;
    }

    return result;
}

bool InOutAlarm::operator==(const InOutAlarm& other) const
{
    return type == other.type && id == other.id && direction == other.direction;
}

void InOutAlarm::parse(const uint8_t* data, int /*size*/)
{
    type = LocationTypes(data[0]);
    id = Utils::endianSwap32(data + 1);
    direction = DirectionTypes(data[5]);
}

std::vector<uint8_t> InOutAlarm::package()
{
    std::vector<uint8_t> result;
    result.push_back(6);
    result.push_back(type);
    Utils::appendU32(id, result);
    result.push_back(direction);

    return result;
}

void InOutAlarm::fromJson(const nlohmann::json& data)
{
    type = data["type"];
    id = data["id"];
    direction = data["direction"];
}

nlohmann::json InOutAlarm::toJson()
{
    return nlohmann::json::object({{"type", type}, {"id", id}, {"direction", direction}});
}

bool PathTimeAlarm::operator==(const PathTimeAlarm& other) const
{
    return id == other.id && time == other.time && result == other.result;
}

void PathTimeAlarm::parse(const uint8_t* data, int /*size*/)
{
    id = Utils::endianSwap32(data);
    time = Utils::endianSwap16(data + 4);
    result = PathTimeResults(data[6]);
}

std::vector<uint8_t> PathTimeAlarm::package()
{
    std::vector<uint8_t> result;
    result.push_back(7);
    Utils::appendU32(id, result);
    Utils::appendU16(time, result);
    result.push_back(this->result);
    return result;
}

void PathTimeAlarm::fromJson(const nlohmann::json& data)
{
    id = data["id"];
    time = data["time"];
    result = data["result"];
}

nlohmann::json PathTimeAlarm::toJson()
{
    return nlohmann::json::object({{"id", id}, {"time", time}, {"result", result}});
}

void ExtendedVehicleSignalFlags::fromJson(const nlohmann::json& data)
{
    bits.highBeam = data["high_beam"];
    bits.lowBeam = data["low_beam"];
    bits.righTurn = data["right_turn"];
    bits.leftTurn = data["left_turn"];
    bits.brake = data["brake"];
    bits.reverse = data["reverse"];
    bits.fog = data["fog"];
    bits.sideMarker = data["side_marker"];
    bits.horn = data["horn"];
    bits.airConditioner = data["air_conditioner"];
    bits.neutral = data["neutral"];
    bits.retarder = data["retarder"];
    bits.abs = data["abs"];
    bits.heater = data["heater"];
    bits.cluth = data["cluth"];
}

nlohmann::json ExtendedVehicleSignalFlags::toJson()
{
    return nlohmann::json::object({{"high_beam", (int)bits.highBeam},
                                   {"low_beam", (int)bits.lowBeam},
                                   {"right_turn", (int)bits.righTurn},
                                   {"left_turn", (int)bits.leftTurn},
                                   {"brake", (int)bits.brake},
                                   {"reverse", (int)bits.reverse},
                                   {"fog", (int)bits.fog},
                                   {"side_marker", (int)bits.sideMarker},
                                   {"horn", (int)bits.horn},
                                   {"air_conditioner", (int)bits.airConditioner},
                                   {"neutral", (int)bits.neutral},
                                   {"retarder", (int)bits.retarder},
                                   {"abs", (int)bits.abs},
                                   {"heater", (int)bits.heater},
                                   {"cluth", (int)bits.cluth}

    });
}

void IOStatusFlags::fromJson(const nlohmann::json& data)
{
    bits.deepSleep = data["deep_sleep"];
    bits.sleep = data["sleep"];
}

nlohmann::json IOStatusFlags::toJson()
{
    return nlohmann::json::object({
        {"deep_sleep", (int)bits.deepSleep},
        {"sleep", (int)bits.sleep},
    });
}

void AnalogFlag::fromJson(const nlohmann::json& data)
{
    bits.ad0 = data["ad0"];
    bits.ad1 = data["ad1"];
}

nlohmann::json AnalogFlag::toJson()
{
    return nlohmann::json::object({
        {"ad0", (int)bits.ad0},
        {"ad1", (int)bits.ad1},
    });
}

}
