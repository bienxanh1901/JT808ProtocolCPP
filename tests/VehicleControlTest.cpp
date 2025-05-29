
#include "JT808/MessageBody/VehicleControl.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class VehicleControlTest : public MessageBodyBaseTest<VehicleControl>
{
protected:
    void SetUp() override
    {
        m_body = new VehicleControl({1});
        m_rawData = {0x01};
        m_object = nlohmann::json::object({{"flag", 1}});
    }
};

TEST_F(VehicleControlTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(VehicleControlTest, TestPackage)
{
    TestPackage();
}

TEST_F(VehicleControlTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(VehicleControlTest, TestToJson)
{
    TestToJson();
}

}
