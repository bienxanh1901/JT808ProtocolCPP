
#include "JT808/MessageBody/InformationServiceMenuSetting.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class InformationServiceMenuSettingTest : public MessageBodyBaseTest<InformationServiceMenuSetting>
{
protected:
    void SetUp() override
    {
        std::vector<InformationServiceMenuSetting::MenuItem> const menus = {{123, "Hello World"}, {123, "JT808"}};
        m_body = new InformationServiceMenuSetting(InformationServiceMenuSetting::AppendMenu, menus);
        m_rawData = {0x2,  0x2,  0x7b, 0x0,  0xb,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57,
                     0x6f, 0x72, 0x6c, 0x64, 0x7b, 0x0,  0x5,  0x4a, 0x54, 0x38, 0x30, 0x38};
        m_object = Json::object({{"type", InformationServiceMenuSetting::AppendMenu},
                                 {"length", 2},
                                 {"menus",
                                  Json::array({Json::object({{"type", 123}, {"info", "Hello World"}}),
                                               Json::object({{"type", 123}, {"info", "JT808"}})})}});
    }
};

TEST_F(InformationServiceMenuSettingTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(InformationServiceMenuSettingTest, TestPackage)
{
    TestPackage();
}

TEST_F(InformationServiceMenuSettingTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(InformationServiceMenuSettingTest, TestToJson)
{
    TestToJson();
}
}
