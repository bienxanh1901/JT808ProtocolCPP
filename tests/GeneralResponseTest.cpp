
#include "JT808/MessageBody/GeneralResponse.h"
#include "MessageBodyBaseTest.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class GeneralResponseTest : public MessageBodyBaseTest<GeneralResponse>
{
protected:
    void SetUp() override
    {
        m_body = new GeneralResponse(123, 456, GeneralResponse::Succeeded);
        m_rawData = {0x0, 0x7b, 0x1, 0xc8, 0x0};
        m_object = {{"seq", 123}, {"id", 456}, "result", 0};
    }
};

TEST_F(GeneralResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(GeneralResponseTest, TestParseFailed1)
{
    GeneralResponse body;
    body.parse(std::vector<uint8_t>(3));

    EXPECT_FALSE(body.isValid());

    body.parse(std::vector<uint8_t>(20));

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
