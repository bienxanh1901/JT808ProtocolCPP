
#include "JT808/MessageBody/LocationDataBulkUpload.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "JT808/MessageBody/LocationInformation.h"
#include "MessageBodyBaseTest.h"
#include "nlohmann/json.hpp"
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class LocationDataBulkUploadTest : public MessageBodyBaseTest<LocationDataBulkUpload>
{
protected:
    void SetUp() override
    {
        BasicLocationInformation basic({.value = 12345}, {.value = 54321}, 10755241, 1066569743, 10, 25, 45,
                                       "700101000000");
        ExtraLocationInformation extra;

        std::vector<LocationInformation> const locations = {
            {basic, extra}, {basic, extra}, {basic, extra}, {basic, extra}, {basic, extra}};

        Json const location_json = Json::object({{"basic",
                                                  Json::object({{"alarm", 12345},
                                                                {"status", 54321},
                                                                {"latitude", 10755241},
                                                                {"longitude", 1066569743},
                                                                {"altitude", 10},
                                                                {"speed", 25},
                                                                {"bearing", 45},
                                                                {"time", "700101000000"}})}});

        Json locations_json = Json::array({
            location_json,
            location_json,
            location_json,
            location_json,
            location_json,
        });

        m_body = new LocationDataBulkUpload(LocationDataBulkUpload::RegularReport, locations);
        m_rawData = {0x0,  0x5,  0x0,  0x0,  0x1c, 0x0,  0x0,  0x30, 0x39, 0x0,  0x0,  0xd4, 0x31, 0x0,  0xa4, 0x1c,
                     0xa9, 0x3f, 0x92, 0x90, 0xf,  0x0,  0xa,  0x0,  0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,  0x0,  0x0,
                     0x0,  0x0,  0x1c, 0x0,  0x0,  0x30, 0x39, 0x0,  0x0,  0xd4, 0x31, 0x0,  0xa4, 0x1c, 0xa9, 0x3f,
                     0x92, 0x90, 0xf,  0x0,  0xa,  0x0,  0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,  0x0,  0x0,  0x0,  0x0,
                     0x1c, 0x0,  0x0,  0x30, 0x39, 0x0,  0x0,  0xd4, 0x31, 0x0,  0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90,
                     0xf,  0x0,  0xa,  0x0,  0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,  0x0,  0x0,  0x0,  0x0,  0x1c, 0x0,
                     0x0,  0x30, 0x39, 0x0,  0x0,  0xd4, 0x31, 0x0,  0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,  0x0,
                     0xa,  0x0,  0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,  0x0,  0x0,  0x0,  0x0,  0x1c, 0x0,  0x0,  0x30,
                     0x39, 0x0,  0x0,  0xd4, 0x31, 0x0,  0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,  0x0,  0xa,  0x0,
                     0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,  0x0,  0x0,  0x0};
        m_object = Json::object(
            {{"type", LocationDataBulkUpload::RegularReport}, {"length", 5}, {"locations", locations_json}});
    }
};

TEST_F(LocationDataBulkUploadTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(LocationDataBulkUploadTest, TestPackage)
{
    TestPackage();
}

TEST_F(LocationDataBulkUploadTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(LocationDataBulkUploadTest, TestToJson)
{
    TestToJson();
}

}
