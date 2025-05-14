
#include "JT808/MessageBody/SubPackageRetransmissionRequest.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class SubPackageRetransmissionRequestTest : public MessageBodyBaseTest<SubPackageRetransmissionRequest>
{
protected:
    ~SubPackageRetransmissionRequestTest() override { }

    void SetUp() override
    {
        m_body = new SubPackageRetransmissionRequest(123, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        m_rawData = {0x0, 0x7b, 0xa, 0x0, 0x1, 0x0, 0x2, 0x0, 0x3, 0x0, 0x4, 0x0,
                     0x5, 0x0,  0x6, 0x0, 0x7, 0x0, 0x8, 0x0, 0x9, 0x0, 0xa};
    }
};

TEST_F(SubPackageRetransmissionRequestTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(SubPackageRetransmissionRequestTest, TestPackage)
{
    TestPackage();
}

}
