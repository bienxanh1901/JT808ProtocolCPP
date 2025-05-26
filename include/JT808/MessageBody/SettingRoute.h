#ifndef SETTINGROUTE_H
#define SETTINGROUTE_H

#include "AreaSettingProperties.h"
#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class SettingRoute : public MessageBodyBase
{
public:
    union RouteProperties {
        struct
        {
            uint8_t drivingTime : 1;
            uint8_t speedLimit : 1;
            uint8_t sideLat : 1; // South or North
            uint8_t sideLng : 1; // East or West
            uint8_t reserved : 4;
        } bits;
        uint8_t value;
    };

    struct Point
    {
        uint32_t id = 0;
        uint32_t lat = 0;
        uint32_t lng = 0;
        uint8_t width = 0;
        RouteProperties flag = {0};
        uint16_t maxDrivingTime = 0;
        uint16_t minDrivingTime = 0;
        uint16_t maxSpeed = 0;
        uint8_t overspeedDuration = 0;

        bool operator==(const Point& other) const
        {
            return id == other.id && flag.value == other.flag.value && lat == other.lat && lng == other.lng
                && width == other.width && maxDrivingTime == other.maxDrivingTime
                && minDrivingTime == other.minDrivingTime && maxSpeed == other.maxSpeed
                && overspeedDuration == other.overspeedDuration;
        }
    };

    SettingRoute() = default;
    SettingRoute(uint32_t id, AreaProperties flag, const std::string& startTime, const std::string& endTime,
                 const std::vector<Point>& points);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const SettingRoute& other);

    uint32_t id() const;
    void setId(uint32_t newId);
    AreaProperties flag() const;
    void setFlag(const AreaProperties& newFlag);
    std::string startTime() const;
    void setStartTime(const std::string& newStartTime);
    std::string endTime() const;
    void setEndTime(const std::string& newEndTime);
    uint16_t length() const;
    void setLength(uint16_t newLength);
    std::vector<Point> points() const;
    void setPoints(const std::vector<Point>& newPoints);

private:
    uint32_t m_id = 0;
    AreaProperties m_flag = {0};
    std::string m_startTime;
    std::string m_endTime;
    uint16_t m_length = 0;
    std::vector<Point> m_points;
};

}
#endif // SETTINGROUTE_H
