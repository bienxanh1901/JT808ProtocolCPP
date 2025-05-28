
#include "JT808/MessageBody/DrivingRecordDataUpload.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class DrivingRecordDataUploadTest : public MessageBodyBaseTest<DrivingRecordDataUpload>
{
protected:
    void SetUp() override
    {
        m_body = new DrivingRecordDataUpload(123, 0x01, "DrivingRecordDataUpload");
        m_rawData = {0x0,  0x7b, 0x1,  0x44, 0x72, 0x69, 0x76, 0x69, 0x6e, 0x67, 0x52, 0x65, 0x63,
                     0x6f, 0x72, 0x64, 0x44, 0x61, 0x74, 0x61, 0x55, 0x70, 0x6c, 0x6f, 0x61, 0x64};
    }
};

TEST_F(DrivingRecordDataUploadTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(DrivingRecordDataUploadTest, TestPackage)
{
    TestPackage();
}

}
