
#include "JT808/MessageBody/DrivingRecordCommand.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class DrivingRecordDataCollectionCommandTest : public MessageBodyBaseTest<DrivingRecordCommand>
{
protected:
    ~DrivingRecordDataCollectionCommandTest() override { }

    void SetUp() override
    {
        m_body = new DrivingRecordCommand(0x01, "DrivingRecordDataCollectionCommand");
        m_rawData = {0x1,  0x44, 0x72, 0x69, 0x76, 0x69, 0x6e, 0x67, 0x52, 0x65, 0x63, 0x6f,
                     0x72, 0x64, 0x44, 0x61, 0x74, 0x61, 0x43, 0x6f, 0x6c, 0x6c, 0x65, 0x63,
                     0x74, 0x69, 0x6f, 0x6e, 0x43, 0x6f, 0x6d, 0x6d, 0x61, 0x6e, 0x64};
    }
};

TEST_F(DrivingRecordDataCollectionCommandTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(DrivingRecordDataCollectionCommandTest, TestPackage)
{
    TestPackage();
}

}
