
#include "JT808/MessageBody/TerminalAuthentication.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class TerminalAuthenticationTest : public MessageBodyBaseTest<TerminalAuthentication>
{
protected:
    void SetUp() override
    {
        m_body = new TerminalAuthentication("HelloJT808Protocol");
        m_rawData = {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x4a, 0x54, 0x38, 0x30,
                     0x38, 0x50, 0x72, 0x6f, 0x74, 0x6f, 0x63, 0x6f, 0x6c};
        m_object = Json::object({{"auth_code", "HelloJT808Protocol"}});
    }
};

TEST_F(TerminalAuthenticationTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalAuthenticationTest, TestPackage)
{
    TestPackage();
}

TEST_F(TerminalAuthenticationTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(TerminalAuthenticationTest, TestToJson)
{
    TestToJson();
}

}
