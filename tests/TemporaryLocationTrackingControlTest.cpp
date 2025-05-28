
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

}
