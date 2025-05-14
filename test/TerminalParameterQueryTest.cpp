
#include "JT808/MessageBody/TerminalParameterQuery.h"
#include "JT808/MessageBody/TerminalParameter.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class TerminalParameterQueryTest : public MessageBodyBaseTest<TerminalParameterQuery>
{
protected:
    ~TerminalParameterQueryTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0xa,  0x0, 0x0, 0x0, 0x1,  0x0, 0x0, 0x0, 0x2,  0x0, 0x0,  0x0, 0x3, 0x0,
                     0x0,  0x0, 0x4, 0x0, 0x0,  0x0, 0x5, 0x0, 0x0,  0x0, 0x20, 0x0, 0x0, 0x0,
                     0x91, 0x0, 0x0, 0x0, 0x13, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0,  0x0, 0x12};
        m_body->setLength(10);
        m_body->setIds({HeartBeatInterval, TCPMsgResponseTimeout, TCPMsgRetransmissTime, UDPMsgResponseTimeout,
                        UDPMsgRetransmissTime, LocationReportStrategy, GNSSBaudrate, MainServerAddress,
                        MainServerUserName, MainServerPassword});
    }
};

TEST_F(TerminalParameterQueryTest, TestParseSuccess)
{
    TerminalParameterQuery body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.length(), m_body->length());
    EXPECT_EQ(body.length(), body.ids().size());
    EXPECT_EQ(body.ids(), m_body->ids());
}

TEST_F(TerminalParameterQueryTest, TestPackage)
{
    TestPackage();
}

}
}
