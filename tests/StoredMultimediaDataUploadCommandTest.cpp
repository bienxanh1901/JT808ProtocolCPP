#include "JT808/MessageBody/StoredMultimediaDataUploadCommand.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class StoredMultimediaDataUploadCommandTest : public MessageBodyBaseTest<StoredMultimediaDataUploadCommand>
{
protected:
    ~StoredMultimediaDataUploadCommandTest() override { }

    void SetUp() override
    {
        m_body = new StoredMultimediaDataUploadCommand(ImageType, 2, PlaformCommand, "250101000000", "250531000000", 1);
        m_rawData = {0x0, 0x2, 0x0, 0x25, 0x1, 0x1, 0x0, 0x0, 0x0, 0x25, 0x5, 0x31, 0x0, 0x0, 0x0, 0x01};
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

}
