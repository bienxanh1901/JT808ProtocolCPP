#include "JT808/MessageBody/LocationInformationQueryResponse.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class LocationInformationQueryResponseTest : public MessageBodyBaseTest<LocationInformationQueryResponse>
{
protected:
    void SetUp() override
    {
        BasicLocationInformation const basic({.value = 12345}, {.value = 54321}, 10755241, 1066569743, 10, 25, 45,
                                             "700101000000");
        ExtraLocationInformation extra;

        m_body = new LocationInformationQueryResponse(123, basic, extra);
        m_rawData = {0x0,  0x7b, 0x0, 0x0, 0x30, 0x39, 0x0,  0x0, 0xd4, 0x31, 0x0,  0xa4, 0x1c, 0xa9, 0x3f,
                     0x92, 0x90, 0xf, 0x0, 0xa,  0x0,  0x19, 0x0, 0x2d, 0x70, 0x01, 0x01, 0x00, 0x00, 0x00};
        m_object = Json::object({{"seq", 123},
                                 {"location",
                                  Json::object({{"basic",
                                                 Json::object({{"alarm", 12345},
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

TEST_F(LocationInformationQueryResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(LocationInformationQueryResponseTest, TestPackage)
{
    TestPackage();
}

TEST_F(LocationInformationQueryResponseTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(LocationInformationQueryResponseTest, TestToJson)
{
    TestToJson();
}

}
