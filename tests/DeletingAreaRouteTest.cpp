#include "JT808/MessageBody/DeletingAreaRoute.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class DeletingAreaRouteTest : public MessageBodyBaseTest<DeletingAreaRoute>
{
protected:
    void SetUp() override
    {
        m_body = new DeletingAreaRoute({123, 456, 678});
        m_rawData = {0x3, 0x0, 0x0, 0x0, 0x7b, 0x0, 0x0, 0x1, 0xc8, 0x0, 0x0, 0x2, 0xa6};
        m_object = nlohmann::json::object({{"length", 3}, {"ids", {123, 456, 678}}});
    }
};

TEST_F(DeletingAreaRouteTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(DeletingAreaRouteTest, TestPackage)
{
    TestPackage();
}

TEST_F(DeletingAreaRouteTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(DeletingAreaRouteTest, TestToJson)
{
    TestToJson();
}

}
