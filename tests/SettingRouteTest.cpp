
#include "JT808/MessageBody/SettingRoute.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class SettingRouteTest : public MessageBodyBaseTest<SettingRoute>
{
protected:
    ~SettingRouteTest() override { }

    void SetUp() override
    {
        std::vector<SettingRoute::Point> points {{.id = 0,
                                                  .lat = 10755241,
                                                  .lng = 1066569743,
                                                  .width = 20,
                                                  .flag = {.value = 1},
                                                  .maxDrivingTime = 600,
                                                  .minDrivingTime = 300},
                                                 {.id = 0,
                                                  .lat = 10755241,
                                                  .lng = 1066569743,
                                                  .width = 20,
                                                  .flag = {.value = 2},
                                                  .maxSpeed = 80,
                                                  .overspeedDuration = 30}};

        m_body = new SettingRoute(123, {1}, "250501000000", "250531000000", points);
        m_rawData = {0x0,  0x0,  0x0,  0x7b, 0x0,  0x1,  0x25, 0x5,  0x1,  0x0, 0x0,  0x0,  0x25, 0x5,
                     0x31, 0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x0,  0x0, 0xa4, 0x1c, 0xa9, 0x3f,
                     0x92, 0x90, 0xf,  0x14, 0x1,  0x2,  0x58, 0x1,  0x2c, 0x0, 0x0,  0x0,  0x0,  0x0,
                     0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,  0x14, 0x2,  0x0, 0x50, 0x1e};
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

}
