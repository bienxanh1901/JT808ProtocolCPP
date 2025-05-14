
#include "JT808/MessageBody/TerminalControl.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class TerminalControlTest : public MessageBodyBaseTest<TerminalControl>
{
protected:
    ~TerminalControlTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x1,  0x66, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x61, 0x64, 0x6d, 0x69, 0x6e, 0x3a, 0x43, 0x6d,
                     0x73, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x56, 0x36, 0x2e, 0x40, 0x31, 0x32, 0x37, 0x2e,
                     0x30, 0x2e, 0x30, 0x2e, 0x31, 0x3a, 0x38, 0x38, 0x38, 0x38, 0x2f, 0x46, 0x54, 0x50, 0x2f,
                     0x30, 0x32, 0x5f, 0x56, 0x4e, 0x32, 0x34, 0x30, 0x36, 0x31, 0x39, 0x2e, 0x62, 0x69, 0x6e};
        m_body->setCommand(TerminalControl::WirelessUpgrade);
        m_body->setParam("ftp://admin:CmsServerV6.@127.0.0.1:8888/FTP/02_VN240619.bin");
    }
};

TEST_F(TerminalControlTest, TestParseSuccess)
{
    TerminalControl body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.command(), m_body->command());
    EXPECT_EQ(body.param(), m_body->param());
}

TEST_F(TerminalControlTest, TestPackage)
{
    TestPackage();
}

}
}
