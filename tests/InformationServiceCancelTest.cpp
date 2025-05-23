
#include "JT808/MessageBody/InformationServiceCancel.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class InformationServiceCancelTest : public MessageBodyBaseTest<InformationServiceCancel>
{
protected:
    ~InformationServiceCancelTest() override { }

    void SetUp() override
    {
        m_body = new InformationServiceCancel(123, 1);
        m_rawData = {0x7b, 0x1};
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

}
