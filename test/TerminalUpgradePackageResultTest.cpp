
#include "JT808/MessageBody/TerminalUpgradePackageResult.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class TerminalUpgradePackageResultTest : public MessageBodyBaseTest<TerminalUpgradePackageResult>
{
protected:
    ~TerminalUpgradePackageResultTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x0, 0x0};

        m_body->setType(Terminal);
        m_body->setResult(TerminalUpgradePackageResult::Succeeded);
    }
};

TEST_F(TerminalUpgradePackageResultTest, TestParseSuccess)
{
    TerminalUpgradePackageResult body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.type(), m_body->type());
    EXPECT_EQ(body.result(), m_body->result());
}

TEST_F(TerminalUpgradePackageResultTest, TestPackage)
{
    TestPackage();
}

}
}
