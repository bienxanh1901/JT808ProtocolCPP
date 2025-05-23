
#include "JT808/MessageBody/InformationServiceMenuSetting.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class InformationServiceMenuSettingTest : public MessageBodyBaseTest<InformationServiceMenuSetting>
{
protected:
    ~InformationServiceMenuSettingTest() override { }

    void SetUp() override
    {
        std::vector<InformationServiceMenuSetting::MenuItem> menus = {
            {.type = 123, .length = 11, .info = "Hello World"}, {.type = 123, .length = 5, .info = "JT808"}};
        m_body = new InformationServiceMenuSetting(InformationServiceMenuSetting::AppendMenu, menus);
        m_rawData = {0x2,  0x2,  0x7b, 0x0,  0xb,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57,
                     0x6f, 0x72, 0x6c, 0x64, 0x7b, 0x0,  0x5,  0x4a, 0x54, 0x38, 0x30, 0x38};
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

}
