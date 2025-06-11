
#include "JT808/MessageBody/MultimediaEventInformationUpload.h"
#include "JT808/MessageBody/Multimedia.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class MultimediaEventInformationUploadTest : public MessageBodyBaseTest<MultimediaEventInformationUpload>
{
protected:
    void SetUp() override
    {
        m_body = new MultimediaEventInformationUpload({123, ImageType, JPEGFormat, PlaformCommand, 2});
        m_rawData = {0x0, 0x0, 0x0, 0x7b, 0x0, 0x0, 0x0, 0x2};
        m_object = Json::object(
            {{"id", 123}, {"type", ImageType}, {"format", JPEGFormat}, {"event", PlaformCommand}, {"channel", 2}});
    }
};

TEST_F(MultimediaEventInformationUploadTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(MultimediaEventInformationUploadTest, TestPackage)
{
    TestPackage();
}

TEST_F(MultimediaEventInformationUploadTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(MultimediaEventInformationUploadTest, TestToJson)
{
    TestToJson();
}
}
