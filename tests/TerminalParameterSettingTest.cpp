
#include "JT808/MessageBody/TerminalParameterSetting.h"
#include "JT808/MessageBody/TerminalParameter.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>
#include <string>

namespace JT808::MessageBody {
class TerminalParameterSettingTest : public MessageBodyBaseTest<TerminalParameterSetting>
{
protected:
    void SetUp() override
    {
        std::string const addr("192.168.8.78");
        std::string const user("JimiIOT");
        std::string const pass("JimiIOT");

        TerminalParameters const params = {{.id = HeartBeatInterval, .num = {.value = 60}},
                                           {.id = TCPMsgResponseTimeout, .num = {.value = 30}},
                                           {.id = TCPMsgRetransmissTime, .num = {.value = 30}},
                                           {.id = UDPMsgResponseTimeout, .num = {.value = 30}},
                                           {.id = UDPMsgRetransmissTime, .num = {.value = 30}},
                                           {.id = LocationReportStrategy, .num = {.value = RegularReportStrategy}},
                                           {.id = GNSSBaudrate, .num = {.value = GNSSBRT115200}},
                                           {.id = MainServerAddress, .str = addr},
                                           {.id = MainServerUserName, .str = user},
                                           {.id = MainServerPassword, .str = pass}};

        m_body = new TerminalParameterSetting(params);
        m_rawData = {0xa,  0x0,  0x0,  0x0,  0x1,  0x4,  0x0,  0x0,  0x0,  0x3c, 0x0,  0x0,  0x0,  0x2,  0x4,
                     0x0,  0x0,  0x0,  0x1e, 0x0,  0x0,  0x0,  0x3,  0x4,  0x0,  0x0,  0x0,  0x1e, 0x0,  0x0,
                     0x0,  0x4,  0x4,  0x0,  0x0,  0x0,  0x1e, 0x0,  0x0,  0x0,  0x5,  0x4,  0x0,  0x0,  0x0,
                     0x1e, 0x0,  0x0,  0x0,  0x20, 0x4,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x91, 0x1,
                     0x5,  0x0,  0x0,  0x0,  0x13, 0xc,  0x31, 0x39, 0x32, 0x2e, 0x31, 0x36, 0x38, 0x2e, 0x38,
                     0x2e, 0x37, 0x38, 0x0,  0x0,  0x0,  0x11, 0x7,  0x4a, 0x69, 0x6d, 0x69, 0x49, 0x4f, 0x54,
                     0x0,  0x0,  0x0,  0x12, 0x7,  0x4a, 0x69, 0x6d, 0x69, 0x49, 0x4f, 0x54};
        m_object = nlohmann::json::object({{"length", 10},
                                           {"params",
                                            nlohmann::json::array({
                                                {{"id", HeartBeatInterval}, {"value", 60}},
                                                {{"id", TCPMsgResponseTimeout}, {"value", 30}},
                                                {{"id", TCPMsgRetransmissTime}, {"value", 30}},
                                                {{"id", UDPMsgResponseTimeout}, {"value", 30}},
                                                {{"id", UDPMsgRetransmissTime}, {"value", 30}},
                                                {{"id", LocationReportStrategy}, {"value", RegularReportStrategy}},
                                                {{"id", GNSSBaudrate}, {"value", GNSSBRT115200}},
                                                {{"id", MainServerAddress}, {"value", addr}},
                                                {{"id", MainServerUserName}, {"value", user}},
                                                {{"id", MainServerPassword}, {"value", pass}},

                                            })}});
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

TEST_F(TerminalParameterSettingTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(TerminalParameterSettingTest, TestToJson)
{
    TestToJson();
}

}
