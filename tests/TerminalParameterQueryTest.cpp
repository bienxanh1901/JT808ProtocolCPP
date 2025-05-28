
#include "JT808/MessageBody/TerminalParameterQuery.h"
#include "JT808/MessageBody/TerminalParameter.h"
#include "MessageBodyBaseTest.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class TerminalParameterQueryTest : public MessageBodyBaseTest<TerminalParameterQuery>
{
protected:
    void SetUp() override
    {
        std::vector<uint32_t> const data {HeartBeatInterval,     TCPMsgResponseTimeout, TCPMsgRetransmissTime,
                                          UDPMsgResponseTimeout, UDPMsgRetransmissTime, LocationReportStrategy,
                                          GNSSBaudrate,          MainServerAddress,     MainServerUserName,
                                          MainServerPassword};
        m_body = new TerminalParameterQuery(data);
        m_rawData = {0xa,  0x0, 0x0, 0x0, 0x1,  0x0, 0x0, 0x0, 0x2,  0x0, 0x0,  0x0, 0x3, 0x0,
                     0x0,  0x0, 0x4, 0x0, 0x0,  0x0, 0x5, 0x0, 0x0,  0x0, 0x20, 0x0, 0x0, 0x0,
                     0x91, 0x0, 0x0, 0x0, 0x13, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0,  0x0, 0x12};
    }
};

TEST_F(TerminalParameterQueryTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalParameterQueryTest, TestPackage)
{
    TestPackage();
}

}
