
#include "JT808/MessageBody/SettingArea.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class SettingCircleAreaTest : public MessageBodyBaseTest<SettingArea>
{
protected:
    ~SettingCircleAreaTest() override { }

    void SetUp() override
    {
        std::vector<AreaItem> areas {{.id = 0,
                                      .flag = {.value = 1},
                                      .centerLat = 10755241,
                                      .centerLng = 1066569743,
                                      .radius = 1000,
                                      .startTime = "250501000000",
                                      .endTime = "250531000000"},
                                     {.id = 1,
                                      .flag = {.value = 2},
                                      .centerLat = 10855241,
                                      .centerLng = 1076569743,
                                      .radius = 1000,
                                      .maxSpeed = 80,
                                      .overspeedDuration = 30}};
        m_body = new SettingArea(CircleArea, AppendArea, areas);
        m_rawData = {0x1,  0x2,  0x0,  0x0,  0x0, 0x0,  0x0,  0x1,  0x0, 0xa4, 0x1c, 0xa9, 0x3f, 0x92,
                     0x90, 0xf,  0x0,  0x0,  0x3, 0xe8, 0x25, 0x5,  0x1, 0x0,  0x0,  0x0,  0x25, 0x5,
                     0x31, 0x0,  0x0,  0x0,  0x0, 0x0,  0x0,  0x1,  0x0, 0x2,  0x0,  0xa5, 0xa3, 0x49,
                     0x40, 0x2b, 0x26, 0x8f, 0x0, 0x0,  0x3,  0xe8, 0x0, 0x50, 0x1e};
    }

    void TestParse() override
    {
        SettingArea body(CircleArea);
        body.parse(m_rawData);

        EXPECT_TRUE(body.isValid());
        EXPECT_TRUE(m_body->operator==(body));
    }
};

TEST_F(SettingCircleAreaTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(SettingCircleAreaTest, TestPackage)
{
    TestPackage();
}

}
