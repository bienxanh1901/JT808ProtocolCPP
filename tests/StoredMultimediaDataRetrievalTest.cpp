#include "JT808/MessageBody/StoredMultimediaDataRetrieval.h"
#include "JT808/MessageBody/Multimedia.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class StoredMultimediaDataRetrievalTest : public MessageBodyBaseTest<StoredMultimediaDataRetrieval>
{
protected:
    void SetUp() override
    {
        m_body = new StoredMultimediaDataRetrieval(ImageType, 2, PlaformCommand, "250101000000", "250531000000");
        m_rawData = {0x0, 0x2, 0x0, 0x25, 0x1, 0x1, 0x0, 0x0, 0x0, 0x25, 0x5, 0x31, 0x0, 0x0, 0x0};
        m_object = nlohmann::json::object({
            {"type", ImageType},
            {"channel", 2},
            {"event", PlaformCommand},
            {"start_time", "250101000000"},
            {"end_time", "250531000000"},
        });
    }
};

TEST_F(StoredMultimediaDataRetrievalTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(StoredMultimediaDataRetrievalTest, TestPackage)
{
    TestPackage();
}

TEST_F(StoredMultimediaDataRetrievalTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(StoredMultimediaDataRetrievalTest, TestToJson)
{
    TestToJson();
}

}
