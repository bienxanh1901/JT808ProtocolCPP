
#include "JT808/MessageBody/MultimediaDataUploadResponse.h"
#include "MessageBodyBaseTest.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class MultimediaDataUploadResponseTest : public MessageBodyBaseTest<MultimediaDataUploadResponse>
{
protected:
    void SetUp() override
    {
        std::vector<uint16_t> ids {456, 789, 222, 555};
        m_body = new MultimediaDataUploadResponse(123, ids);
        m_rawData = {0x0, 0x0, 0x0, 0x7b, 0x4, 0x1, 0xc8, 0x3, 0x15, 0x0, 0xde, 0x2, 0x2b};
    }
};

TEST_F(MultimediaDataUploadResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(MultimediaDataUploadResponseTest, TestPackage)
{
    TestPackage();
}

}
