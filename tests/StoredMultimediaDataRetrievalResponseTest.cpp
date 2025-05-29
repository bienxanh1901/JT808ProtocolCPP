#include "JT808/MessageBody/StoredMultimediaDataRetrievalResponse.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/Multimedia.h"
#include "MessageBodyBaseTest.h"
#include "nlohmann/json.hpp"
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class StoredMultimediaDataRetrievalResponseTest : public MessageBodyBaseTest<StoredMultimediaDataRetrievalResponse>
{
protected:
    void SetUp() override
    {
        BasicLocationInformation location({.value = 12345}, {.value = 54321}, 10755241, 1066569743, 10, 25, 45,
                                          "700101000000");

        nlohmann::json const location_json = nlohmann::json::object({{"alarm", 12345},
                                                                     {"status", 54321},
                                                                     {"latitude", 10755241},
                                                                     {"longitude", 1066569743},
                                                                     {"altitude", 10},
                                                                     {"speed", 25},
                                                                     {"bearing", 45},
                                                                     {"time", "700101000000"}});
        std::vector<MultimediaRetrievalData> const result = {
            {123, ImageType, 2, PlaformCommand, location}, {234, ImageType, 2, PlaformCommand, location},
            {345, ImageType, 2, PlaformCommand, location}, {456, ImageType, 2, PlaformCommand, location},
            {567, ImageType, 2, PlaformCommand, location}, {678, ImageType, 2, PlaformCommand, location},
        };
        m_body = new StoredMultimediaDataRetrievalResponse(123, result);
        m_rawData = {
            0x0,  0x7b, 0x0,  0x6,  0x0,  0x0,  0x0,  0x7b, 0x0,  0x2,  0x0,  0x0,  0x0,  0x30, 0x39, 0x0,  0x0,  0xd4,
            0x31, 0x0,  0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,  0x0,  0xa,  0x0,  0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,
            0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xea, 0x0,  0x2,  0x0,  0x0,  0x0,  0x30, 0x39, 0x0,  0x0,  0xd4, 0x31,
            0x0,  0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,  0x0,  0xa,  0x0,  0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,  0x0,
            0x0,  0x0,  0x0,  0x0,  0x1,  0x59, 0x0,  0x2,  0x0,  0x0,  0x0,  0x30, 0x39, 0x0,  0x0,  0xd4, 0x31, 0x0,
            0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,  0x0,  0xa,  0x0,  0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,  0x0,  0x0,
            0x0,  0x0,  0x0,  0x1,  0xc8, 0x0,  0x2,  0x0,  0x0,  0x0,  0x30, 0x39, 0x0,  0x0,  0xd4, 0x31, 0x0,  0xa4,
            0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,  0x0,  0xa,  0x0,  0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,  0x0,  0x0,  0x0,
            0x0,  0x0,  0x2,  0x37, 0x0,  0x2,  0x0,  0x0,  0x0,  0x30, 0x39, 0x0,  0x0,  0xd4, 0x31, 0x0,  0xa4, 0x1c,
            0xa9, 0x3f, 0x92, 0x90, 0xf,  0x0,  0xa,  0x0,  0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,  0x0,  0x0,  0x0,  0x0,
            0x0,  0x2,  0xa6, 0x0,  0x2,  0x0,  0x0,  0x0,  0x30, 0x39, 0x0,  0x0,  0xd4, 0x31, 0x0,  0xa4, 0x1c, 0xa9,
            0x3f, 0x92, 0x90, 0xf,  0x0,  0xa,  0x0,  0x19, 0x0,  0x2d, 0x70, 0x1,  0x1,  0x0,  0x0,  0x0};

        m_object = nlohmann::json::object({{"seq", 123},
                                           {"length", 6},
                                           {"result",
                                            nlohmann::json::array({
                                                nlohmann::json::object({
                                                    {"id", 123},
                                                    {"type", ImageType},
                                                    {"event", PlaformCommand},
                                                    {"channel", 2},
                                                    {"location", location_json},
                                                }),
                                                nlohmann::json::object({
                                                    {"id", 234},
                                                    {"type", ImageType},
                                                    {"event", PlaformCommand},
                                                    {"channel", 2},
                                                    {"location", location_json},
                                                }),
                                                nlohmann::json::object({
                                                    {"id", 345},
                                                    {"type", ImageType},
                                                    {"event", PlaformCommand},
                                                    {"channel", 2},
                                                    {"location", location_json},
                                                }),
                                                nlohmann::json::object({
                                                    {"id", 456},
                                                    {"type", ImageType},
                                                    {"event", PlaformCommand},
                                                    {"channel", 2},
                                                    {"location", location_json},
                                                }),
                                                nlohmann::json::object({
                                                    {"id", 567},
                                                    {"type", ImageType},
                                                    {"event", PlaformCommand},
                                                    {"channel", 2},
                                                    {"location", location_json},
                                                }),
                                                nlohmann::json::object({
                                                    {"id", 678},
                                                    {"type", ImageType},
                                                    {"event", PlaformCommand},
                                                    {"channel", 2},
                                                    {"location", location_json},
                                                }),
                                            })}});
    }
};

TEST_F(StoredMultimediaDataRetrievalResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(StoredMultimediaDataRetrievalResponseTest, TestPackage)
{
    TestPackage();
}

TEST_F(StoredMultimediaDataRetrievalResponseTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(StoredMultimediaDataRetrievalResponseTest, TestToJson)
{
    TestToJson();
}

}
