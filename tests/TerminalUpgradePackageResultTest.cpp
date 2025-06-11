
#include "JT808/MessageBody/TerminalUpgradePackageResult.h"
#include "JT808/MessageBody/TerminalUpgradePackage.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class TerminalUpgradePackageResultTest : public MessageBodyBaseTest<TerminalUpgradePackageResult>
{
protected:
    void SetUp() override
    {
        m_body = new TerminalUpgradePackageResult(Terminal, TerminalUpgradePackageResult::Succeeded);
        m_rawData = {0x0, 0x0};
        m_object = Json::object({{"type", Terminal}, {"result", TerminalUpgradePackageResult::Succeeded}});
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

TEST_F(TerminalUpgradePackageResultTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(TerminalUpgradePackageResultTest, TestToJson)
{
    TestToJson();
}

}
