
#include "JT808/MessageBody/ImmediateCameraCaptureCommand.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class ImmediateCameraCaptureCommandTest : public MessageBodyBaseTest<ImmediateCameraCaptureCommand>
{
protected:
    ~ImmediateCameraCaptureCommandTest() override { }

    void SetUp() override
    {
        m_body = new ImmediateCameraCaptureCommand(
            123, 3, 30, LocalStorage, ImmediateCameraCaptureCommand::Resolution1024x768, 10, 120, 127, 127, 120);
        m_rawData = {0x7b, 0x0, 0x3, 0x0, 0x1e, 0x1, 0x4, 0xa, 0x78, 0x7f, 0x7f, 0x78};
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

}
