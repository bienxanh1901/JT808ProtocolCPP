
#include "JT808/MessageBody/SettingPolygonArea.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class SettingPolygonAreaTest : public MessageBodyBaseTest<SettingPolygonArea>
{
protected:
    void SetUp() override
    {
        std::vector<SettingPolygonArea::Point> const points {
            {10755241, 1066569743}, {10756241, 1066579743}, {10757241, 1066589743}, {10758241, 1066599743},
            {10759241, 1066519743}, {10751241, 1066539743}, {10752241, 1066549743},
        };
        m_body = new SettingPolygonArea(123, {1}, "250501000000", "250531000000", 0, 0, points);
        m_rawData = {0x0,  0x0,  0x0,  0x7b, 0x0,  0x1,  0x25, 0x5,  0x1,  0x0,  0x0,  0x0,  0x25, 0x5,  0x31,
                     0x0,  0x0,  0x0,  0x7,  0x0,  0xa4, 0x1c, 0xa9, 0x3f, 0x92, 0x90, 0xf,  0x0,  0xa4, 0x20,
                     0x91, 0x3f, 0x92, 0xb7, 0x1f, 0x0,  0xa4, 0x24, 0x79, 0x3f, 0x92, 0xde, 0x2f, 0x0,  0xa4,
                     0x28, 0x61, 0x3f, 0x93, 0x5,  0x3f, 0x0,  0xa4, 0x2c, 0x49, 0x3f, 0x91, 0xcc, 0xbf, 0x0,
                     0xa4, 0xd,  0x9,  0x3f, 0x92, 0x1a, 0xdf, 0x0,  0xa4, 0x10, 0xf1, 0x3f, 0x92, 0x41, 0xef};
        m_object = Json::object({{"id", 123},
                                 {"flag", 1},
                                 {"start_time", "250501000000"},
                                 {"end_time", "250531000000"},
                                 {"length", 7},
                                 {"points",
                                  Json::array({Json::object({{"lat", 10755241}, {"lng", 1066569743}}),
                                               Json::object({{"lat", 10756241}, {"lng", 1066579743}}),
                                               Json::object({{"lat", 10757241}, {"lng", 1066589743}}),
                                               Json::object({{"lat", 10758241}, {"lng", 1066599743}}),
                                               Json::object({{"lat", 10759241}, {"lng", 1066519743}}),
                                               Json::object({{"lat", 10751241}, {"lng", 1066539743}}),
                                               Json::object({{"lat", 10752241}, {"lng", 1066549743}})})}});
    }
};

TEST_F(SettingPolygonAreaTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(SettingPolygonAreaTest, TestPackage)
{
    TestPackage();
}

TEST_F(SettingPolygonAreaTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(SettingPolygonAreaTest, TestToJson)
{
    TestToJson();
}

}
