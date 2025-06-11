#ifndef SETTINGPOLYGONAREA_H
#define SETTINGPOLYGONAREA_H

#include "AreaSettingProperties.h"
#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

namespace JT808::MessageBody {

class SettingPolygonArea : public MessageBodyBase
{
public:
    struct Point
    {
        uint32_t lat = 0;
        uint32_t lng = 0;

        bool operator==(const Point& other) const;
        int parse(const uint8_t* data, int size);
        ByteArray package() const;

        void fromJson(const Json& data);
        Json toJson();
    };

    SettingPolygonArea();
    SettingPolygonArea(uint32_t id, AreaProperties flag, std::string startTime, std::string endTime, uint16_t maxSpeed,
                       uint8_t overspeedDuration, const std::vector<Point>& points);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const SettingPolygonArea& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint32_t id() const;
    void setId(uint32_t newId);
    AreaProperties flag() const;
    void setFlag(const AreaProperties& newFlag);
    std::string startTime() const;
    void setStartTime(const std::string& newStartTime);
    std::string endTime() const;
    void setEndTime(const std::string& newEndTime);
    uint16_t maxSpeed() const;
    void setMaxSpeed(uint16_t newMaxSpeed);
    uint8_t overspeedDuration() const;
    void setOverspeedDuration(uint8_t newOverspeedDuration);
    std::vector<Point> points() const;
    void setPoints(const std::vector<Point>& newPoints);

private:
    uint32_t m_id = 0;
    AreaProperties m_flag = {0};
    std::string m_startTime;
    std::string m_endTime;
    uint16_t m_maxSpeed = 0;
    uint8_t m_overspeedDuration = 0;
    std::vector<Point> m_points;
};

}
#endif // SETTINGPOLYGONAREA_H
