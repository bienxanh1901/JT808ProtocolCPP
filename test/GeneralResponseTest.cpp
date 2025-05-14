
#include "JT808/MessageBody/GeneralResponse.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class GeneralResponseTest : public MessageBodyBaseTest<GeneralResponse>
{
protected:
    ~GeneralResponseTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x0, 0x7b, 0x1, 0xc8, 0x0};
        m_body->setSeq(123);
        m_body->setId(456);
        m_body->setResult(GeneralResponse::Succeeded);
    }
};

TEST_F(GeneralResponseTest, TestParseSuccess)
{
    GeneralResponse body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.seq(), m_body->seq());
    EXPECT_EQ(body.id(), m_body->id());
    EXPECT_EQ(body.result(), m_body->result());
}

TEST_F(GeneralResponseTest, TestParseFailed1)
{
    GeneralResponse body;
    body.parse();

    EXPECT_FALSE(body.isValid());

    body.setRawData(std::vector<uint8_t>(20));
    body.parse();

    EXPECT_FALSE(body.isValid());
}

TEST_F(GeneralResponseTest, TestPackage)
{
    TestPackage();
}

}
}
