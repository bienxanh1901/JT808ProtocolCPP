
#include "JT808/MessageBody/MultimediaDataUpload.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/Multimedia.h"
#include "MessageBodyBaseTest.h"
#include "nlohmann/json.hpp"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class MultimediaDataUploadTest : public MessageBodyBaseTest<MultimediaDataUpload>
{
protected:
    void SetUp() override
    {
        BasicLocationInformation const location({.value = 12345}, {.value = 54321}, 10755241, 1066569743, 10, 25, 45,
                                                "700101000000");

        Json const location_json = Json::object({{"alarm", 12345},
                                                 {"status", 54321},
                                                 {"latitude", 10755241},
                                                 {"longitude", 1066569743},
                                                 {"altitude", 10},
                                                 {"speed", 25},
                                                 {"bearing", 45},
                                                 {"time", "700101000000"}});

        m_body = new MultimediaDataUpload({123, ImageType, JPEGFormat, PlaformCommand, 2}, location,
                                          {0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x74, 0x65, 0x73, 0x74,
                                           0x20, 0x6d, 0x65, 0x64, 0x69, 0x61, 0x20, 0x64, 0x61, 0x74, 0x61});
        m_rawData = {0x0,  0x0,  0x0,  0x7b, 0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x30, 0x39, 0x0,  0x0,  0xd4,
                     0x31, 0x0,  0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,  0x0,  0xa,  0x0,  0x19, 0x0,  0x2d,
                     0x70, 0x1,  0x1,  0x0,  0x0,  0x0,  0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x74,
                     0x65, 0x73, 0x74, 0x20, 0x6d, 0x65, 0x64, 0x69, 0x61, 0x20, 0x64, 0x61, 0x74, 0x61};

        m_object = Json::object({{"info",
                                  Json::object({{"id", 123},
                                                {"type", ImageType},
                                                {"format", JPEGFormat},
                                                {"event", PlaformCommand},
                                                {"channel", 2}})},
                                 {"location", location_json},
                                 {"multimedia", {0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x74, 0x65, 0x73, 0x74,
                                                 0x20, 0x6d, 0x65, 0x64, 0x69, 0x61, 0x20, 0x64, 0x61, 0x74, 0x61}}

        });
    }
};

TEST_F(MultimediaDataUploadTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(MultimediaDataUploadTest, TestPackage)
{
    TestPackage();
}

TEST_F(MultimediaDataUploadTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(MultimediaDataUploadTest, TestToJson)
{
    TestToJson();
}

}
