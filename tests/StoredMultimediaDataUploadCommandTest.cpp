#include "JT808/MessageBody/StoredMultimediaDataUploadCommand.h"
#include "JT808/MessageBody/Multimedia.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class StoredMultimediaDataUploadCommandTest : public MessageBodyBaseTest<StoredMultimediaDataUploadCommand>
{
protected:
    void SetUp() override
    {
        m_body = new StoredMultimediaDataUploadCommand(ImageType, 2, PlaformCommand, "250101000000", "250531000000", 1);
        m_rawData = {0x0, 0x2, 0x0, 0x25, 0x1, 0x1, 0x0, 0x0, 0x0, 0x25, 0x5, 0x31, 0x0, 0x0, 0x0, 0x01};
        m_object = Json::object({{"type", ImageType},
                                 {"channel", 2},
                                 {"event", PlaformCommand},
                                 {"start_time", "250101000000"},
                                 {"end_time", "250531000000"},
                                 {"delete", 1}});
    }
};

TEST_F(StoredMultimediaDataUploadCommandTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(StoredMultimediaDataUploadCommandTest, TestPackage)
{
    TestPackage();
}

TEST_F(StoredMultimediaDataUploadCommandTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(StoredMultimediaDataUploadCommandTest, TestToJson)
{
    TestToJson();
}

}
