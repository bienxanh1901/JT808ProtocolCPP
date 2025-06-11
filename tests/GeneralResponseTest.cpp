
#include "JT808/MessageBody/GeneralResponse.h"
#include "JT808/MessageIds.h"
#include "MessageBodyBaseTest.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class GeneralResponseTest : public MessageBodyBaseTest<GeneralResponse>
{
protected:
    void SetUp() override
    {
        m_body = new GeneralResponse(123, TerminalAuthenticationMsgId, GeneralResponse::Succeeded);
        m_rawData = {0x0, 0x7b, 0x1, 0x2, 0x0};
        m_object =
            Json::object({{"seq", 123}, {"id", TerminalAuthenticationMsgId}, {"result", GeneralResponse::Succeeded}});
    }
};

TEST_F(GeneralResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(GeneralResponseTest, TestParseFailed1)
{
    GeneralResponse body;
    body.parse(ByteArray(3));

    EXPECT_FALSE(body.isValid());

    body.parse(ByteArray(20));

    EXPECT_FALSE(body.isValid());
}

TEST_F(GeneralResponseTest, TestPackage)
{
    TestPackage();
}

TEST_F(GeneralResponseTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(GeneralResponseTest, TestToJson)
{
    TestToJson();
}

}
