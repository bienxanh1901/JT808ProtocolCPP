
#include "JT808/MessageBody/InformationServiceCancel.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class InformationServiceCancelTest : public MessageBodyBaseTest<InformationServiceCancel>
{
protected:
    void SetUp() override
    {
        m_body = new InformationServiceCancel(123, 1);
        m_rawData = {0x7b, 0x1};
        m_object = nlohmann::json::object({{"id", 123}, {"flag", 1}});
    }
};

TEST_F(InformationServiceCancelTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(InformationServiceCancelTest, TestPackage)
{
    TestPackage();
}

TEST_F(InformationServiceCancelTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(InformationServiceCancelTest, TestToJson)
{
    TestToJson();
}
}
