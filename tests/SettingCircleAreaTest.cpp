
#include "JT808/MessageBody/SettingCircleArea.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class SettingCircleAreaTest : public MessageBodyBaseTest<SettingCircleArea>
{
protected:
    ~SettingCircleAreaTest() override { }

    void SetUp() override
    {
        std::vector<SettingCircleArea::AreaItem> areas {
            {0, {.value = 1}, 10755241, 1066569743, 1000, "250501000000", "250531000000"},
            {0, {.value = 2}, 10755241, 1066569743, 1000, "", "", 80, 30}};
        m_body = new SettingCircleArea(SettingCircleArea::SettingType::AppendArea, areas);
        m_rawData = {0x1,  0x2,  0x0,  0x0, 0x0, 0x0,  0x0,  0x1,  0x0, 0xa4, 0x1c, 0xa9, 0x3f, 0x92,
                     0x90, 0xf,  0x0,  0x0, 0x3, 0xe8, 0x25, 0x5,  0x1, 0x0,  0x0,  0x0,  0x25, 0x5,
                     0x31, 0x0,  0x0,  0x0, 0x0, 0x0,  0x0,  0x0,  0x0, 0x2,  0x0,  0xa4, 0x1c, 0xa9,
                     0x3f, 0x92, 0x90, 0xf, 0x0, 0x0,  0x3,  0xe8, 0x0, 0x50, 0x1e};
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
