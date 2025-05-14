
#include "JT808/MessageBody/SubPackageRetransmissionRequest.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class SubPackageRetransmissionRequestTest : public MessageBodyBaseTest<SubPackageRetransmissionRequest>
{
protected:
    ~SubPackageRetransmissionRequestTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x0, 0x7b, 0xa, 0x0, 0x1, 0x0, 0x2, 0x0, 0x3, 0x0, 0x4, 0x0,
                     0x5, 0x0,  0x6, 0x0, 0x7, 0x0, 0x8, 0x0, 0x9, 0x0, 0xa};
        m_body->setSeq(123);
        m_body->setLength(10);
        m_body->setIds({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    }
};

TEST_F(SubPackageRetransmissionRequestTest, TestParseSuccess)
{
    SubPackageRetransmissionRequest body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.seq(), m_body->seq());
    EXPECT_EQ(body.length(), m_body->length());
    EXPECT_EQ(body.length(), body.ids().size());
    EXPECT_EQ(body.ids(), m_body->ids());
}

TEST_F(SubPackageRetransmissionRequestTest, TestPackage)
{
    TestPackage();
}

}
}
