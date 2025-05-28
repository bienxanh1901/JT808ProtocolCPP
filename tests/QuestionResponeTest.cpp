
#include "JT808/MessageBody/QuestionResponse.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class QuestionResponseTest : public MessageBodyBaseTest<QuestionResponse>
{
protected:
    void SetUp() override
    {
        m_body = new QuestionResponse(123, 2);
        m_rawData = {0x0, 0x7b, 0x2};
    }
};

TEST_F(QuestionResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(QuestionResponseTest, TestPackage)
{
    TestPackage();
}

}
