#include "JT808/MessageBody/LocationInformationQueryResponse.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {
class LocationInformationQueryResponseTest : public MessageBodyBaseTest<LocationInformationQueryResponse>
{
protected:
    ~LocationInformationQueryResponseTest() override { }

    void SetUp() override
    {
        MessageBodyBaseTest::SetUp();
        m_rawData = {0x0,  0x7b, 0x0, 0x0, 0x30, 0x39, 0x0,  0x0, 0xd4, 0x31, 0x0,  0xa4, 0x1c, 0xa9, 0x3f,
                     0x92, 0x90, 0xf, 0x0, 0xa,  0x0,  0x19, 0x0, 0x2d, 0x70, 0x01, 0x01, 0x00, 0x00, 0x00};

        m_body->setSeq(123);
        m_body->setAlarm({.value = 12345});
        m_body->setStatus({.value = 54321});
        m_body->setLatitude(10755241);
        m_body->setLongitude(1066569743);
        m_body->setAltitude(10);
        m_body->setSpeed(25);
        m_body->setBearing(45);
        m_body->setTime("700101000000"); // 1970-01-01-00-00-00
    }
};

TEST_F(LocationInformationQueryResponseTest, TestParseSuccess)
{
    LocationInformationQueryResponse body(m_rawData);
    body.parse();

    EXPECT_TRUE(body.isValid());
    EXPECT_EQ(body.seq(), m_body->seq());
    EXPECT_EQ(body.alarm().value, m_body->alarm().value);
    EXPECT_EQ(body.status().value, m_body->status().value);
    EXPECT_EQ(body.latitude(), m_body->latitude());
    EXPECT_EQ(body.longitude(), m_body->longitude());
    EXPECT_EQ(body.altitude(), m_body->altitude());
    EXPECT_EQ(body.speed(), m_body->speed());
    EXPECT_EQ(body.bearing(), m_body->bearing());
    EXPECT_EQ(body.time(), m_body->time());
}

TEST_F(LocationInformationQueryResponseTest, TestPackage)
{
    TestPackage();
}

}
}
