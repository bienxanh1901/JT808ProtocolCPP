#include "JT808/MessageBody/StorageMultimediaDataRetrieval.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class StorageMultimediaDataRetrievalTest : public MessageBodyBaseTest<StorageMultimediaDataRetrieval>
{
protected:
    ~StorageMultimediaDataRetrievalTest() override { }

    void SetUp() override
    {
        m_body = new StorageMultimediaDataRetrieval(ImageType, 2, PlaformCommand, "250101000000", "250531000000");
        m_rawData = {0x0, 0x2, 0x0, 0x25, 0x1, 0x1, 0x0, 0x0, 0x0, 0x25, 0x5, 0x31, 0x0, 0x0, 0x0};
    }
};

TEST_F(StorageMultimediaDataRetrievalTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(StorageMultimediaDataRetrievalTest, TestPackage)
{
    TestPackage();
}

}
