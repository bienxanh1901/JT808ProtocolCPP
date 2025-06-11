
#include "JT808/MessageBody/TemporaryLocationTrackingControl.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class TemporaryLocationTrackingControlTest : public MessageBodyBaseTest<TemporaryLocationTrackingControl>
{
protected:
    void SetUp() override
    {
        m_body = new TemporaryLocationTrackingControl(60, 3600);
        m_rawData = {0x0, 0x3c, 0x0, 0x0, 0xe, 0x10};
        m_object = Json::object({{"period", 60}, {"expiry", 3600}});
    }
};

TEST_F(TemporaryLocationTrackingControlTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TemporaryLocationTrackingControlTest, TestPackage)
{
    TestPackage();
}

TEST_F(TemporaryLocationTrackingControlTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(TemporaryLocationTrackingControlTest, TestToJson)
{
    TestToJson();
}

}
