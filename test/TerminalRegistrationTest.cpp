
#include "JT808/MessageBody/TerminalRegistration.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class TerminalRegistrationTest : public MessageBodyBaseTest<TerminalRegistration>
{
protected:
    ~TerminalRegistrationTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x0, 0x40, 0x0, 0x18, 0x1, 0x2,  0x3,  0x4,  0x5,  0x6,  0x7,  0x8,  0x9,  0xa,  0x6, 0x7,
                     0x8, 0x9,  0xa, 0x6,  0x7, 0x8,  0x9,  0xa,  0x6,  0x7,  0x8,  0x9,  0xa,  0x0,  0x1, 0x2,
                     0x3, 0x4,  0x5, 0x6,  0x2, 0x38, 0x36, 0x42, 0x37, 0x2d, 0x31, 0x35, 0x32, 0x36, 0x32};

        m_body->setProvince(64);
        m_body->setCity(24);
        m_body->setManufacturer({0x01, 0x02, 0x03, 0x04, 0x05});
        m_body->setModel({0x06, 0x07, 0x08, 0x09, 0x0A, 0x06, 0x07, 0x08, 0x09, 0x0A,
                          0x06, 0x07, 0x08, 0x09, 0x0A, 0x06, 0x07, 0x08, 0x09, 0x0A});
        m_body->setId({0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06});
        m_body->setColor(Yellow);
        m_body->setVin("86B7-15262");
    }
};

TEST_F(TerminalRegistrationTest, TestParseSuccess)
{
    TerminalRegistration body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.province(), m_body->province());
    EXPECT_EQ(body.city(), m_body->city());
    EXPECT_EQ(body.manufacturer(), m_body->manufacturer());
    EXPECT_EQ(body.model(), m_body->model());
    EXPECT_EQ(body.id(), m_body->id());
    EXPECT_EQ(body.color(), m_body->color());
    EXPECT_EQ(body.vin(), m_body->vin());
}

TEST_F(TerminalRegistrationTest, TestPackage)
{
    TestPackage();
}

}
}
