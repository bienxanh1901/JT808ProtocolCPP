#ifndef BASICLOCATIONINFORMATION_H
#define BASICLOCATIONINFORMATION_H

#include <cstdint>
#include <string>
#include <vector>

#include "LocationInformationCommon.h"
#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class BasicLocationInformation
{

public:
    BasicLocationInformation() = default;
    BasicLocationInformation(const AlarmFlags& alarm, const StatusFlags& status, uint32_t lat, uint32_t lng,
                             uint16_t alt, uint16_t speed, uint16_t bearing, std::string time);
    bool operator==(const BasicLocationInformation& other) const;
    int parse(const uint8_t* data, int size);
    std::vector<uint8_t> package();

    void fromJson(const nlohmann::json& data);
    nlohmann::json toJson();

    AlarmFlags alarm() const;
    void setAlarm(const AlarmFlags& newAlarm);
    StatusFlags status() const;
    void setStatus(const StatusFlags& newStatus);
    uint32_t lat() const;
    void setLat(uint32_t newLat);
    uint32_t lng() const;
    void setLng(uint32_t newLng);
    uint16_t alt() const;
    void setAlt(uint16_t newAlt);
    uint16_t speed() const;
    void setSpeed(uint16_t newSpeed);
    uint16_t bearing() const;
    void setBearing(uint16_t newBearing);
    std::string time() const;
    void setTime(const std::string& newTime);

private:
    AlarmFlags m_alarm = {0};
    StatusFlags m_status = {0};
    uint32_t m_lat = 0;
    uint32_t m_lng = 0;
    uint16_t m_alt = 0;
    uint16_t m_speed = 0;
    uint16_t m_bearing = 0;
    std::string m_time;
};

}
#endif // BASICLOCATIONINFORMATION_H
