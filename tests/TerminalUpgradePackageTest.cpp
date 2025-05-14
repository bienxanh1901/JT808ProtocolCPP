
#include "JT808/MessageBody/TerminalUpgradePackage.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class TerminalUpgradePackageTest : public MessageBodyBaseTest<TerminalUpgradePackage>
{
protected:
    ~TerminalUpgradePackageTest() override { }

    void SetUp() override
    {
        m_body = new TerminalUpgradePackage(Terminal, {0x01, 0x02, 0x03, 0x04, 0x05}, "1.0.0",
                                            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        m_rawData = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x5, 0x31, 0x2e, 0x30, 0x2e, 0x30, 0x0,
                     0x0, 0x0, 0xa, 0x1, 0x2, 0x3, 0x4, 0x5,  0x6,  0x7,  0x8,  0x9,  0xa};
    }
};

TEST_F(TerminalUpgradePackageTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalUpgradePackageTest, TestPackage)
{
    TestPackage();
}

}
