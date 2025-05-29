
#include "JT808/MessageBody/TextMessageDispatch.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class TextMessageDispatchTest : public MessageBodyBaseTest<TextMessageDispatch>
{
protected:
    void SetUp() override
    {
        TextMessageDispatch::Flag const flag {.bits {.sos = 1, .terminalDisplay = 1}};
        m_body = new TextMessageDispatch(flag, "Emergency Message");
        m_rawData = {0x5,  0x45, 0x6d, 0x65, 0x72, 0x67, 0x65, 0x6e, 0x63,
                     0x79, 0x20, 0x4d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65};
        m_object = nlohmann::json::object({{"flag", 5}, {"text", "Emergency Message"}});
    }
};

TEST_F(TextMessageDispatchTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TextMessageDispatchTest, TestPackage)
{
    TestPackage();
}

TEST_F(TextMessageDispatchTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(TextMessageDispatchTest, TestToJson)
{
    TestToJson();
}

}
