
#include "JT808/MessageBody/TerminalRegistrationResponse.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class TerminalRegistrationResponseTest : public MessageBodyBaseTest<TerminalRegistrationResponse>
{
protected:
    ~TerminalRegistrationResponseTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x0,  0x7b, 0x0,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x4a, 0x54, 0x38,
                     0x30, 0x38, 0x50, 0x72, 0x6f, 0x74, 0x6f, 0x63, 0x6f, 0x6c};
        m_body->setSeq(123);
        m_body->setResult(TerminalRegistrationResponse::Succeeded);
        m_body->setAuthCode("HelloJT808Protocol");
    }
};

TEST_F(TerminalRegistrationResponseTest, TestParseSuccess)
{
    TerminalRegistrationResponse body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.seq(), m_body->seq());
    EXPECT_EQ(body.result(), m_body->result());
    EXPECT_EQ(body.authCode(), m_body->authCode());
}

TEST_F(TerminalRegistrationResponseTest, TestPackage)
{
    TestPackage();
}

}
}
