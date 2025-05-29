
#include "JT808/MessageBody/SettingRoute.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class SettingRouteTest : public MessageBodyBaseTest<SettingRoute>
{
protected:
    void SetUp() override
    {
        std::vector<SettingRoute::Point> const points {{.pointId = 0,
                                                        .routeId = 147,
                                                        .lat = 10755241,
                                                        .lng = 1066569743,
                                                        .width = 20,
                                                        .flag = {.value = 1},
                                                        .maxDrivingTime = 600,
                                                        .minDrivingTime = 300},
                                                       {.pointId = 1,
                                                        .routeId = 258,
                                                        .lat = 10755241,
                                                        .lng = 1066569743,
                                                        .width = 20,
                                                        .flag = {.value = 2},
                                                        .maxSpeed = 80,
                                                        .overspeedDuration = 30}};

        m_body = new SettingRoute(123, {1}, "250501000000", "250531000000", points);
        m_rawData = {0x0,  0x0,  0x0,  0x7b, 0x0,  0x1,  0x25, 0x5,  0x1,  0x0,  0x0,  0x0,  0x25, 0x5,  0x31, 0x0,
                     0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x93, 0x0,  0xa4, 0x1c, 0xa9,
                     0x3f, 0x92, 0x90, 0xf,  0x14, 0x1,  0x2,  0x58, 0x1,  0x2c, 0x0,  0x0,  0x0,  0x1,  0x0,  0x0,
                     0x1,  0x2,  0x0,  0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,  0x14, 0x2,  0x0,  0x50, 0x1e};
        m_object =
            nlohmann::json::object({{"id", 123},
                                    {"flag", 1},
                                    {"start_time", "250501000000"},
                                    {"end_time", "250531000000"},
                                    {"length", 2},
                                    {"points",
                                     nlohmann::json::array({nlohmann::json::object({{"point_id", 0},
                                                                                    {"route_id", 147},
                                                                                    {"lat", 10755241},
                                                                                    {"lng", 1066569743},
                                                                                    {"width", 20},
                                                                                    {"flag", 1},
                                                                                    {"passed", 600},
                                                                                    {"uncovered", 300}}),
                                                            nlohmann::json::object({{"point_id", 1},
                                                                                    {"route_id", 258},
                                                                                    {"lat", 10755241},
                                                                                    {"lng", 1066569743},
                                                                                    {"width", 20},
                                                                                    {"flag", 2},
                                                                                    {"max_speed", 80},
                                                                                    {"overspeed_duration", 30}})})}});
    }
};

TEST_F(SettingRouteTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(SettingRouteTest, TestPackage)
{
    TestPackage();
}

TEST_F(SettingRouteTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(SettingRouteTest, TestToJson)
{
    TestToJson();
}

}
