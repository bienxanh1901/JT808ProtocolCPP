
#include "JT808/MessageBody/SingleStoredMultimediaItemRetrievalUploadCommand.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class SingleStoredMultimediaItemRetrievalUploadCommandTest
    : public MessageBodyBaseTest<SingleStoredMultimediaItemRetrievalUploadCommand>
{
protected:
    ~SingleStoredMultimediaItemRetrievalUploadCommandTest() override { }

    void SetUp() override
    {
        m_body = new SingleStoredMultimediaItemRetrievalUploadCommand(123, 1);
        m_rawData = {0x0, 0x0, 0x0, 0x7b, 0x1};
    }
};

TEST_F(SingleStoredMultimediaItemRetrievalUploadCommandTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(SingleStoredMultimediaItemRetrievalUploadCommandTest, TestPackage)
{
    TestPackage();
}

}
