
#include "JT808/MessageBody/TemporaryLocationTrackingControl.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class TemporaryLocationTrackingControlTest : public MessageBodyBaseTest<TemporaryLocationTrackingControl>
{
protected:
    ~TemporaryLocationTrackingControlTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x0, 0x3c, 0x0, 0x0, 0xe, 0x10};
        m_body->setPeriod(60);
        m_body->setExpiry(3600);
    }
};

TEST_F(TemporaryLocationTrackingControlTest, TestParseSuccess)
{
    TemporaryLocationTrackingControl body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.period(), m_body->period());
    EXPECT_EQ(body.expiry(), m_body->expiry());
}

TEST_F(TemporaryLocationTrackingControlTest, TestPackage)
{
    TestPackage();
}

}
}
