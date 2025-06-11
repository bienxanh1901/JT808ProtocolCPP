
#include "JT808/MessageBody/CANBusDataUpload.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class CANBusDataUploadTest : public MessageBodyBaseTest<CANBusDataUpload>
{
protected:
    void SetUp() override
    {
        std::vector<CANBusDataUpload::ItemData> const data {
            {{.bits = {.id = 123, .dataMethod = 0, .frameType = 0, .channel = 1}}, "13245678"},
            {{.bits = {.id = 111, .dataMethod = 1, .frameType = 1, .channel = 0}}, "13245678"},
        };
        m_body = new CANBusDataUpload("1601300000", data);
        m_rawData = {0x0,  0x2,  0x16, 0x1,  0x30, 0x0, 0x0,  0x7b, 0x0,  0x0,  0x80, 0x31, 0x33, 0x32, 0x34, 0x35,
                     0x36, 0x37, 0x38, 0x6f, 0x0,  0x0, 0x60, 0x31, 0x33, 0x32, 0x34, 0x35, 0x36, 0x37, 0x38};
        m_object = Json::object(
            {{"length", 2},
             {"time", "1601300000"},
             {"can_data",
              Json::array(
                  {{{"channel", 1}, {"frame_type", 0}, {"data_method", 0}, {"id", 123}, {"data", "13245678"}},
                   {{"channel", 0}, {"frame_type", 1}, {"data_method", 1}, {"id", 111}, {"data", "13245678"}}})}});
    }
};

TEST_F(CANBusDataUploadTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(CANBusDataUploadTest, TestPackage)
{
    TestPackage();
}

TEST_F(CANBusDataUploadTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(CANBusDataUploadTest, TestToJson)
{
    TestToJson();
}

}
