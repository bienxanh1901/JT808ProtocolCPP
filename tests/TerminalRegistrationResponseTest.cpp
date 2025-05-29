
#include "JT808/MessageBody/TerminalRegistrationResponse.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class TerminalRegistrationResponseTest : public MessageBodyBaseTest<TerminalRegistrationResponse>
{
protected:
    void SetUp() override
    {
        m_body = new TerminalRegistrationResponse(123, TerminalRegistrationResponse::Succeeded, "HelloJT808Protocol");
        m_rawData = {0x0,  0x7b, 0x0,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x4a, 0x54, 0x38,
                     0x30, 0x38, 0x50, 0x72, 0x6f, 0x74, 0x6f, 0x63, 0x6f, 0x6c};
        m_object = nlohmann::json::object(
            {{"seq", 123}, {"result", TerminalRegistrationResponse::Succeeded}, {"auth_code", "HelloJT808Protocol"}});
    }
};

TEST_F(TerminalRegistrationResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalRegistrationResponseTest, TestPackage)
{
    TestPackage();
}

TEST_F(TerminalRegistrationResponseTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(TerminalRegistrationResponseTest, TestToJson)
{
    TestToJson();
}

}
