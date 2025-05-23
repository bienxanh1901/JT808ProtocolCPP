
#include "JT808/MessageBody/VehicleControl.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class VehicleControlTest : public MessageBodyBaseTest<VehicleControl>
{
protected:
    ~VehicleControlTest() override { }

    void SetUp() override
    {
        m_body = new VehicleControl({1});
        m_rawData = {0x01};
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

}
