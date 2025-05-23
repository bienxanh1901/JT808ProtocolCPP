
#include "JT808/MessageBody/DeletingCircleArea.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class DeletingCircleAreaTest : public MessageBodyBaseTest<DeletingCircleArea>
{
protected:
    ~DeletingCircleAreaTest() override { }

    void SetUp() override
    {
        m_body = new DeletingCircleArea({123, 456, 678});
        m_rawData = {0x3, 0x0, 0x0, 0x0, 0x7b, 0x0, 0x0, 0x1, 0xc8, 0x0, 0x0, 0x2, 0xa6};
    }
};

TEST_F(DeletingCircleAreaTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(DeletingCircleAreaTest, TestPackage)
{
    TestPackage();
}

}
