
#include "JT808/MessageBody/EventSetting.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class EventSettingTest : public MessageBodyBaseTest<EventSetting>
{
protected:
    void SetUp() override
    {
        std::vector<EventSetting::Event> const events {
            {0, "HelloWorld"},
            {1, "Hello"},
            {2, "World"},
            {3, "JT808Protocol"},
        };

        m_body = new EventSetting(EventSetting::AppendEvents, events);
        m_rawData = {0x2,  0x4,  0x0,  0xa,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x1,
                     0x5,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2,  0x5,  0x57, 0x6f, 0x72, 0x6c, 0x64, 0x3,  0xd,
                     0x4a, 0x54, 0x38, 0x30, 0x38, 0x50, 0x72, 0x6f, 0x74, 0x6f, 0x63, 0x6f, 0x6c};

        m_object = nlohmann::json::object(
            {{"type", EventSetting::AppendEvents},
             {"length", 4},
             {"events",
              nlohmann::json::array({nlohmann::json::object({{"id", 0}, {"content", "HelloWorld"}}),
                                     nlohmann::json::object({{"id", 1}, {"content", "Hello"}}),
                                     nlohmann::json::object({{"id", 2}, {"content", "World"}}),
                                     nlohmann::json::object({{"id", 3}, {"content", "JT808Protocol"}})})}});
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

TEST_F(EventSettingTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(EventSettingTest, TestToJson)
{
    TestToJson();
}

}
