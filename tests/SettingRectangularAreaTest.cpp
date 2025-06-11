
#include "JT808/MessageBody/AreaSettingProperties.h"
#include "JT808/MessageBody/SettingArea.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class SettingRectangularAreaTest : public MessageBodyBaseTest<SettingArea>
{
protected:
    void SetUp() override
    {
        std::vector<AreaItem> const areas {{.id = 0,
                                            .flag = {.value = 1},
                                            .ltLat = 10755241,
                                            .ltLng = 1066569743,
                                            .rbLat = 10855241,
                                            .rbLng = 1076569743,
                                            .startTime = "250501000000",
                                            .endTime = "250531000000"},
                                           {.id = 1,
                                            .flag = {.value = 2},
                                            .ltLat = 10755241,
                                            .ltLng = 1066569743,
                                            .rbLat = 10855241,
                                            .rbLng = 1076569743,
                                            .maxSpeed = 80,
                                            .overspeedDuration = 30}};
        m_body = new SettingArea(RectangularArea, AppendArea, areas);
        m_rawData = {0x1,  0x2,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x0,  0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,
                     0x0,  0xa5, 0xa3, 0x49, 0x40, 0x2b, 0x26, 0x8f, 0x25, 0x5,  0x1,  0x0,  0x0,  0x0,  0x25, 0x5,
                     0x31, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x0,  0x2,  0x0,  0xa4, 0x1c, 0xa9, 0x3f, 0x92,
                     0x90, 0xf,  0x0,  0xa5, 0xa3, 0x49, 0x40, 0x2b, 0x26, 0x8f, 0x0,  0x50, 0x1e};
        m_object = Json::object({{"type", AppendArea},
                                 {"length", 2},
                                 {"areas",
                                  Json::array({Json::object({{"id", 0},
                                                             {"flag", 1},
                                                             {"lt_lat", 10755241},
                                                             {"lt_lng", 1066569743},
                                                             {"rb_lat", 10855241},
                                                             {"rb_lng", 1076569743},
                                                             {"start_time", "250501000000"},
                                                             {"end_time", "250531000000"}}),
                                               Json::object({{"id", 1},
                                                             {"flag", 2},
                                                             {"lt_lat", 10755241},
                                                             {"lt_lng", 1066569743},
                                                             {"rb_lat", 10855241},
                                                             {"rb_lng", 1076569743},
                                                             {"max_speed", 80},
                                                             {"overspeed_duration", 30}})})}});
    }

    void TestParse() override
    {
        SettingArea body(RectangularArea);
        body.parse(m_rawData);

        EXPECT_TRUE(body.isValid());
        EXPECT_TRUE(m_body->operator==(body));
    }
};

TEST_F(SettingRectangularAreaTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(SettingRectangularAreaTest, TestPackage)
{
    TestPackage();
}

TEST_F(SettingRectangularAreaTest, TestFromJsom)
{
    SettingArea body(RectangularArea);
    ;
    body.fromJson(m_object);
    EXPECT_TRUE(body.isValid());
    EXPECT_TRUE(m_body->operator==(body));
}

TEST_F(SettingRectangularAreaTest, TestToJson)
{
    TestToJson();
}

}
