
#include "JT808/MessageBody/ManualAlarmConfirmation.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class ManualAlarmConfirmationTest : public MessageBodyBaseTest<ManualAlarmConfirmation>
{
protected:
    void SetUp() override
    {
        m_body = new ManualAlarmConfirmation(123, {.value = 1});
        m_rawData = {0x0, 0x7b, 0x0, 0x0, 0x0, 0x1};
        m_object = nlohmann::json::object({{"seq", 123}, {"type", 1}});
    }
};

TEST_F(ManualAlarmConfirmationTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(ManualAlarmConfirmationTest, TestPackage)
{
    TestPackage();
}

TEST_F(ManualAlarmConfirmationTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(ManualAlarmConfirmationTest, TestToJson)
{
    TestToJson();
}

}
