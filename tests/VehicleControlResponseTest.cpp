#include "JT808/MessageBody/VehicleControlResponse.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class VehicleControlResponseTest : public MessageBodyBaseTest<VehicleControlResponse>
{
protected:
    void SetUp() override
    {
        BasicLocationInformation const basic({.value = 12345}, {.value = 54321}, 10755241, 1066569743, 10, 25, 45,
                                             "700101000000");
        ExtraLocationInformation const extra;

        m_body = new VehicleControlResponse(123, basic, extra);
        m_rawData = {0x0,  0x7b, 0x0, 0x0, 0x30, 0x39, 0x0,  0x0, 0xd4, 0x31, 0x0, 0xa4, 0x1c, 0xa9, 0x3f,
                     0x92, 0x90, 0xf, 0x0, 0xa,  0x0,  0x19, 0x0, 0x2d, 0x70, 0x1, 0x1,  0x0,  0x0,  0x0};
        m_object =
            nlohmann::json::object({{"seq", 123},
                                    {"location",
                                     nlohmann::json::object({{"basic",
                                                              nlohmann::json::object({{"alarm", 12345},
                                                                                      {"status", 54321},
                                                                                      {"latitude", 10755241},
                                                                                      {"longitude", 1066569743},
                                                                                      {"altitude", 10},
                                                                                      {"speed", 25},
                                                                                      {"bearing", 45},
                                                                                      {"time", "700101000000"}})}})}

            });
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

TEST_F(VehicleControlResponseTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(VehicleControlResponseTest, TestToJson)
{
    TestToJson();
}

}
