
#include "JT808/MessageBody/ManualAlarmConfirmation.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class ManualAlarmConfirmationTest : public MessageBodyBaseTest<ManualAlarmConfirmation>
{
protected:
    ~ManualAlarmConfirmationTest() override { }

    void SetUp() override
    {
        m_body = new ManualAlarmConfirmation(123, {.value = 1});
        m_rawData = {0x0, 0x7b, 0x0, 0x0, 0x0, 0x1};
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

}
