
#include "JT808/MessageBody/TerminalParameterSetting.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class TerminalParameterSettingTest : public MessageBodyBaseTest<TerminalParameterSetting>
{
protected:
    ~TerminalParameterSettingTest() override { }

    void SetUp() override
    {
        std::string addr("192.168.8.78");
        std::string user("JimiIOT");
        std::string pass("JimiIOT");
        m_body = new TerminalParameterSetting({{HeartBeatInterval, {0, 0, 0, 60}},
                                               {TCPMsgResponseTimeout, {0, 0, 0, 30}},
                                               {TCPMsgRetransmissTime, {0, 0, 0, 30}},
                                               {UDPMsgResponseTimeout, {0, 0, 0, 30}},
                                               {UDPMsgRetransmissTime, {0, 0, 0, 30}},
                                               {LocationReportStrategy, {RegularReportStrategy}},
                                               {GNSSBaudrate, {GNSSBRT115200}},
                                               {MainServerAddress, {addr.begin(), addr.end()}},
                                               {MainServerUserName, {user.begin(), user.end()}},
                                               {MainServerPassword, {pass.begin(), pass.end()}}});
        m_rawData = {0xa,  0x0,  0x0,  0x0,  0x1,  0x4,  0x0,  0x0,  0x0,  0x3c, 0x0,  0x0,  0x0,  0x2,  0x4,
                     0x0,  0x0,  0x0,  0x1e, 0x0,  0x0,  0x0,  0x3,  0x4,  0x0,  0x0,  0x0,  0x1e, 0x0,  0x0,
                     0x0,  0x4,  0x4,  0x0,  0x0,  0x0,  0x1e, 0x0,  0x0,  0x0,  0x5,  0x4,  0x0,  0x0,  0x0,
                     0x1e, 0x0,  0x0,  0x0,  0x11, 0x7,  0x4a, 0x69, 0x6d, 0x69, 0x49, 0x4f, 0x54, 0x0,  0x0,
                     0x0,  0x12, 0x7,  0x4a, 0x69, 0x6d, 0x69, 0x49, 0x4f, 0x54, 0x0,  0x0,  0x0,  0x13, 0xc,
                     0x31, 0x39, 0x32, 0x2e, 0x31, 0x36, 0x38, 0x2e, 0x38, 0x2e, 0x37, 0x38, 0x0,  0x0,  0x0,
                     0x20, 0x1,  0x0,  0x0,  0x0,  0x0,  0x91, 0x1,  0x5};
    }
};

TEST_F(TerminalParameterSettingTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalParameterSettingTest, TestPackage)
{
    TestPackage();
}

}
