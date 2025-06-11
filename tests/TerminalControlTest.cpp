
#include "JT808/MessageBody/TerminalControl.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class TerminalControlTest : public MessageBodyBaseTest<TerminalControl>
{
protected:
    void SetUp() override
    {
        m_body = new TerminalControl(TerminalControl::WirelessUpgrade,
                                     "ftp://admin:CmsServerV6.@127.0.0.1:8888/FTP/02_VN240619.bin");
        m_rawData = {0x1,  0x66, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x61, 0x64, 0x6d, 0x69, 0x6e, 0x3a, 0x43, 0x6d,
                     0x73, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x56, 0x36, 0x2e, 0x40, 0x31, 0x32, 0x37, 0x2e,
                     0x30, 0x2e, 0x30, 0x2e, 0x31, 0x3a, 0x38, 0x38, 0x38, 0x38, 0x2f, 0x46, 0x54, 0x50, 0x2f,
                     0x30, 0x32, 0x5f, 0x56, 0x4e, 0x32, 0x34, 0x30, 0x36, 0x31, 0x39, 0x2e, 0x62, 0x69, 0x6e};
        m_object = Json::object({{"command", TerminalControl::WirelessUpgrade},
                                 {"param", "ftp://admin:CmsServerV6.@127.0.0.1:8888/FTP/02_VN240619.bin"}});
    }
};

TEST_F(TerminalControlTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalControlTest, TestPackage)
{
    TestPackage();
}

TEST_F(TerminalControlTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(TerminalControlTest, TestToJson)
{
    TestToJson();
}

}
