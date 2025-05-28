
#include "JT808/MessageBody/EventSetting.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class EventSettingTest : public MessageBodyBaseTest<EventSetting>
{
protected:
    ~EventSettingTest() override { }

    void SetUp() override
    {
        std::vector<EventSetting::Event> events {
            {0, "HelloWorld"},
            {1, "Hello"},
            {2, "World"},
            {3, "JT808Protocol"},
        };

        m_body = new EventSetting(EventSetting::AppendEvents, events);
        m_rawData = {0x2,  0x4,  0x0,  0xa,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x1,
                     0x5,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2,  0x5,  0x57, 0x6f, 0x72, 0x6c, 0x64, 0x3,  0xd,
                     0x4a, 0x54, 0x38, 0x30, 0x38, 0x50, 0x72, 0x6f, 0x74, 0x6f, 0x63, 0x6f, 0x6c};
    }
};

TEST_F(EventSettingTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(EventSettingTest, TestPackage)
{
    TestPackage();
}

}
