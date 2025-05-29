
#include "JT808/MessageBody/SingleStoredMultimediaItemRetrievalUploadCommand.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class SingleStoredMultimediaItemRetrievalUploadCommandTest
    : public MessageBodyBaseTest<SingleStoredMultimediaItemRetrievalUploadCommand>
{
protected:
    void SetUp() override
    {
        m_body = new SingleStoredMultimediaItemRetrievalUploadCommand(123, 1);
        m_rawData = {0x0, 0x0, 0x0, 0x7b, 0x1};
        m_object = nlohmann::json::object({{"id", 123}, {"delete", 1}});
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

TEST_F(SingleStoredMultimediaItemRetrievalUploadCommandTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(SingleStoredMultimediaItemRetrievalUploadCommandTest, TestToJson)
{
    TestToJson();
}

}
