
#include "JT808/MessageBody/TerminalUpgradePackageResult.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class TerminalUpgradePackageResultTest : public MessageBodyBaseTest<TerminalUpgradePackageResult>
{
protected:
    ~TerminalUpgradePackageResultTest() override { }

    void SetUp() override
    {
        m_body = new TerminalUpgradePackageResult(Terminal, TerminalUpgradePackageResult::Succeeded);
        m_rawData = {0x0, 0x0};
    }
};

TEST_F(TerminalUpgradePackageResultTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalUpgradePackageResultTest, TestPackage)
{
    TestPackage();
}

}
