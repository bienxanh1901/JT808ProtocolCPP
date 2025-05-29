
#include "JT808/MessageBody/ImmediateCameraCaptureCommand.h"
#include "JT808/MessageBody/Multimedia.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class ImmediateCameraCaptureCommandTest : public MessageBodyBaseTest<ImmediateCameraCaptureCommand>
{
protected:
    void SetUp() override
    {
        m_body = new ImmediateCameraCaptureCommand(
            2, 3, 30, LocalStorage, ImmediateCameraCaptureCommand::Resolution1024x768, 10, 120, 127, 127, 120);
        m_rawData = {0x02, 0x0, 0x3, 0x0, 0x1e, 0x1, 0x4, 0xa, 0x78, 0x7f, 0x7f, 0x78};
        m_object = nlohmann::json::object({{"channel", 2},
                                           {"command", 3},
                                           {"period", 30},
                                           {"saving", LocalStorage},
                                           {"resolution", ImmediateCameraCaptureCommand::Resolution1024x768},
                                           {"quality", 10},
                                           {"brightness", 120},
                                           {"contrast", 127},
                                           {"saturation", 127},
                                           {"chroma", 120}});
    }
};

TEST_F(ImmediateCameraCaptureCommandTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(ImmediateCameraCaptureCommandTest, TestPackage)
{
    TestPackage();
}

TEST_F(ImmediateCameraCaptureCommandTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(ImmediateCameraCaptureCommandTest, TestToJson)
{
    TestToJson();
}

}
