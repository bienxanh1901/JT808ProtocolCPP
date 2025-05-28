
#include "JT808/MessageBody/TerminalParameterQueryResponse.h"
#include "JT808/MessageBody/TerminalParameter.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>
#include <string>

namespace JT808::MessageBody {
class TerminalParameterQueryResponseTest : public MessageBodyBaseTest<TerminalParameterQueryResponse>
{
protected:
    void SetUp() override
    {
        std::string const addr("192.168.8.78");
        std::string const user("JimiIOT");
        std::string const pass("JimiIOT");
        m_body = new TerminalParameterQueryResponse(123,
                                                    {{HeartBeatInterval, {0, 0, 0, 60}},
                                                     {TCPMsgResponseTimeout, {0, 0, 0, 30}},
                                                     {TCPMsgRetransmissTime, {0, 0, 0, 30}},
                                                     {UDPMsgResponseTimeout, {0, 0, 0, 30}},
                                                     {UDPMsgRetransmissTime, {0, 0, 0, 30}},
                                                     {LocationReportStrategy, {RegularReportStrategy}},
                                                     {GNSSBaudrate, {GNSSBRT115200}},
                                                     {MainServerAddress, {addr.begin(), addr.end()}},
                                                     {MainServerUserName, {user.begin(), user.end()}},
                                                     {MainServerPassword, {pass.begin(), pass.end()}}});
        m_rawData = {0x0,  0x7b, 0xa,  0x0,  0x0,  0x0,  0x1,  0x4,  0x0,  0x0,  0x0,  0x3c, 0x0,  0x0,  0x0,
                     0x2,  0x4,  0x0,  0x0,  0x0,  0x1e, 0x0,  0x0,  0x0,  0x3,  0x4,  0x0,  0x0,  0x0,  0x1e,
                     0x0,  0x0,  0x0,  0x4,  0x4,  0x0,  0x0,  0x0,  0x1e, 0x0,  0x0,  0x0,  0x5,  0x4,  0x0,
                     0x0,  0x0,  0x1e, 0x0,  0x0,  0x0,  0x11, 0x7,  0x4a, 0x69, 0x6d, 0x69, 0x49, 0x4f, 0x54,
                     0x0,  0x0,  0x0,  0x12, 0x7,  0x4a, 0x69, 0x6d, 0x69, 0x49, 0x4f, 0x54, 0x0,  0x0,  0x0,
                     0x13, 0xc,  0x31, 0x39, 0x32, 0x2e, 0x31, 0x36, 0x38, 0x2e, 0x38, 0x2e, 0x37, 0x38, 0x0,
                     0x0,  0x0,  0x20, 0x1,  0x0,  0x0,  0x0,  0x0,  0x91, 0x1,  0x5};
    }
};

TEST_F(TerminalParameterQueryResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalParameterQueryResponseTest, TestPackage)
{
    TestPackage();
}

}
