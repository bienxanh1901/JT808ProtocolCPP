
#include "JT808/MessageBody/ImmediateCameraCaptureCommandResponse.h"
#include "MessageBodyBaseTest.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class ImmediateCameraCaptureCommandResponseTest : public MessageBodyBaseTest<ImmediateCameraCaptureCommandResponse>
{
protected:
    void SetUp() override
    {
        std::vector<uint32_t> const ids {123, 456, 789, 111, 222, 333, 444, 666};
        m_body = new ImmediateCameraCaptureCommandResponse(123, ImmediateCameraCaptureCommandResponse::Succeeded, ids);
        m_rawData = {0x0, 0x7b, 0x0,  0x0,  0x8, 0x0, 0x0,  0x0,  0x7b, 0x0, 0x0, 0x1,  0xc8,
                     0x0, 0x0,  0x3,  0x15, 0x0, 0x0, 0x0,  0x6f, 0x0,  0x0, 0x0, 0xde, 0x0,
                     0x0, 0x1,  0x4d, 0x0,  0x0, 0x1, 0xbc, 0x0,  0x0,  0x2, 0x9a};
    }
};

TEST_F(ImmediateCameraCaptureCommandResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(ImmediateCameraCaptureCommandResponseTest, TestPackage)
{
    TestPackage();
}

}
