
#include "JT808/MessageBody/AudioRecordingStartCommand.h"
#include "JT808/MessageBody/Multimedia.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class AudioRecordingStartCommandTest : public MessageBodyBaseTest<AudioRecordingStartCommand>
{
protected:
    void SetUp() override
    {
        m_body = new AudioRecordingStartCommand(AudioRecordingStartCommand::StartCommand, 300, RealTimeUpload,
                                                AudioRecordingStartCommand::AudioSamplingRate8K);
        m_rawData = {0x1, 0x1, 0x2c, 0x0, 0x0};
    }
};

TEST_F(AudioRecordingStartCommandTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(AudioRecordingStartCommandTest, TestPackage)
{
    TestPackage();
}

}
