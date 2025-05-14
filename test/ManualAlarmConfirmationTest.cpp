
#include "JT808/MessageBody/ManualAlarmConfirmation.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class ManualAlarmConfirmationTest : public MessageBodyBaseTest<ManualAlarmConfirmation>
{
protected:
    ~ManualAlarmConfirmationTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x0, 0x7b, 0x0, 0x0, 0x0, 0x1};
        m_body->setSeq(123);
        m_body->setType({.value = 1});
    }
};

TEST_F(ManualAlarmConfirmationTest, TestParseSuccess)
{
    ManualAlarmConfirmation body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.seq(), m_body->seq());
    EXPECT_EQ(body.type().value, m_body->type().value);
}

TEST_F(ManualAlarmConfirmationTest, TestPackage)
{
    TestPackage();
}

}
}
