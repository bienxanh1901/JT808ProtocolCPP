
#include "JT808/MessageBody/TerminalUpgradePackage.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class TerminalUpgradePackageTest : public MessageBodyBaseTest<TerminalUpgradePackage>
{
protected:
    ~TerminalUpgradePackageTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x5, 0x31, 0x2e, 0x30, 0x2e, 0x30, 0x0,
                     0x0, 0x0, 0xa, 0x1, 0x2, 0x3, 0x4, 0x5,  0x6,  0x7,  0x8,  0x9,  0xa};
        m_body->setType(Terminal);
        m_body->setManufacturer({0x01, 0x02, 0x03, 0x04, 0x05});
        m_body->setVerLen(5);
        m_body->setVersion("1.0.0");
        m_body->setFwLen(10);
        m_body->setFirmware({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    }
};

TEST_F(TerminalUpgradePackageTest, TestParseSuccess)
{
    TerminalUpgradePackage body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.type(), m_body->type());
    EXPECT_EQ(body.manufacturer(), m_body->manufacturer());
    EXPECT_EQ(body.verLen(), m_body->verLen());
    EXPECT_EQ(body.verLen(), body.version().length());
    EXPECT_EQ(body.version(), m_body->version());
    EXPECT_EQ(body.fwLen(), m_body->fwLen());
    EXPECT_EQ(body.fwLen(), body.firmware().size());
    EXPECT_EQ(body.firmware(), m_body->firmware());
}

TEST_F(TerminalUpgradePackageTest, TestPackage)
{
    TestPackage();
}

}
}
