#include "JT808/MessageBody/VehicleControlResponse.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class VehicleControlResponseTest : public MessageBodyBaseTest<VehicleControlResponse>
{
protected:
    void SetUp() override
    {
        m_body = new VehicleControlResponse(123, {.value = 12345}, {.value = 54321}, 10755241, 1066569743, 10, 25, 45,
                                            "700101000000");
        m_rawData = {0x0,  0x7b, 0x0, 0x0, 0x30, 0x39, 0x0,  0x0, 0xd4, 0x31, 0x0,  0xa4, 0x1c, 0xa9, 0x3f,
                     0x92, 0x90, 0xf, 0x0, 0xa,  0x0,  0x19, 0x0, 0x2d, 0x70, 0x01, 0x01, 0x00, 0x00, 0x00};
    }
};

TEST_F(VehicleControlResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(VehicleControlResponseTest, TestPackage)
{
    TestPackage();
}

}
