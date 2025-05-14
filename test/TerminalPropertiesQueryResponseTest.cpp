
#include "JT808/MessageBody/TerminalPropertiesQueryResponse.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class TerminalPropertiesQueryResponseTest : public MessageBodyBaseTest<TerminalPropertiesQueryResponse>
{
protected:
    ~TerminalPropertiesQueryResponseTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x0,  0x1,  0x1,  0x2,  0x3,  0x4,  0x5,  0x6,  0x7,  0x8,  0x9,  0xa,  0x6,  0x7,  0x8,
                     0x9,  0xa,  0x6,  0x7,  0x8,  0x9,  0xa,  0x6,  0x7,  0x8,  0x9,  0xa,  0x0,  0x1,  0x2,
                     0x3,  0x4,  0x5,  0x6,  0x89, 0x61, 0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x23, 0x45, 0x5,
                     0x31, 0x2e, 0x31, 0x2e, 0x30, 0x5,  0x32, 0x2e, 0x30, 0x2e, 0x35, 0x80, 0x40};
        m_body->setType({.value = 1});
        m_body->setManufacturer({0x01, 0x02, 0x03, 0x04, 0x05});
        m_body->setModel({0x06, 0x07, 0x08, 0x09, 0x0A, 0x06, 0x07, 0x08, 0x09, 0x0A,
                          0x06, 0x07, 0x08, 0x09, 0x0A, 0x06, 0x07, 0x08, 0x09, 0x0A});
        m_body->setId({0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06});
        m_body->setIccid("89610000000000012345");
        m_body->setHwVersionLen(5);
        m_body->setHwVersion("1.1.0");
        m_body->setFwVersionLen(5);
        m_body->setFwVersion("2.0.5");
        m_body->setGnssProp({.value = 128});
        m_body->setCommProp({.value = 64});
    }
};

TEST_F(TerminalPropertiesQueryResponseTest, TestParseSuccess)
{
    TerminalPropertiesQueryResponse body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.type().value, m_body->type().value);
    EXPECT_EQ(body.manufacturer(), m_body->manufacturer());
    EXPECT_EQ(body.model(), m_body->model());
    EXPECT_EQ(body.id(), m_body->id());
    EXPECT_EQ(body.iccid(), m_body->iccid());
    EXPECT_EQ(body.hwVersionLen(), m_body->hwVersionLen());
    EXPECT_EQ(body.hwVersionLen(), body.hwVersion().length());
    EXPECT_EQ(body.hwVersion(), m_body->hwVersion());
    EXPECT_EQ(body.fwVersionLen(), m_body->fwVersionLen());
    EXPECT_EQ(body.fwVersionLen(), body.fwVersion().length());
    EXPECT_EQ(body.fwVersion(), m_body->fwVersion());
    EXPECT_EQ(body.gnssProp().value, m_body->gnssProp().value);
    EXPECT_EQ(body.commProp().value, m_body->commProp().value);
}

TEST_F(TerminalPropertiesQueryResponseTest, TestPackage)
{
    TestPackage();
}

}
}
