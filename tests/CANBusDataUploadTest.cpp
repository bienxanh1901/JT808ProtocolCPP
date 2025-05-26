
#include "JT808/MessageBody/CANBusDataUpload.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class CANBusDataUploadTest : public MessageBodyBaseTest<CANBusDataUpload>
{
protected:
    ~CANBusDataUploadTest() override { }

    void SetUp() override
    {
        std::vector<CANBusDataUpload::ItemData> data {
            {{.value = 123}, {.value = 456}},
            {{.value = 789}, {.value = 112233}},
        };
        m_body = new CANBusDataUpload("1601300000", data);
        m_rawData = {0x0, 0x2, 0x16, 0x1,  0x30, 0x0, 0x0, 0x7b, 0x0,  0x0, 0x0, 0xc8, 0x1, 0x0, 0x0, 0x0,
                     0x0, 0x0, 0x0,  0x15, 0x3,  0x0, 0x0, 0x69, 0xb6, 0x1, 0x0, 0x0,  0x0, 0x0, 0x0};
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

}
