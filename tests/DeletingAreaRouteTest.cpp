#include "JT808/MessageBody/DeletingAreaRoute.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class DeletingAreaRouteTest : public MessageBodyBaseTest<DeletingAreaRoute>
{
protected:
    ~DeletingAreaRouteTest() override { }

    void SetUp() override
    {
        m_body = new DeletingAreaRoute({123, 456, 678});
        m_rawData = {0x3, 0x0, 0x0, 0x0, 0x7b, 0x0, 0x0, 0x1, 0xc8, 0x0, 0x0, 0x2, 0xa6};
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

}
