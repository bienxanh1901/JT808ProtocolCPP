#ifndef AUDIORECORDINGSTARTCOMMAND_H
#define AUDIORECORDINGSTARTCOMMAND_H

#include "MessageBodyBase.h"
#include "Multimedia.h"

namespace JT808::MessageBody {

class AudioRecordingStartCommand : public MessageBodyBase
{
public:
    enum Commands : uint8_t
    {
        StopCommand = 0x00,
        StartCommand = 0x01
    };

    enum AudioSamplingRates : uint8_t
    {
        AudioSamplingRate8K = 0,
        AudioSamplingRate11K = 1,
        AudioSamplingRate23K = 2,
        AudioSamplingRate32K = 3
    };

    AudioRecordingStartCommand() = default;
    AudioRecordingStartCommand(Commands command, uint16_t time, SavingMethods saving, AudioSamplingRates rate);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const AudioRecordingStartCommand& other) const;

    Commands command() const;
    void setCommand(Commands newCommand);
    uint16_t time() const;
    void setTime(uint16_t newTime);
    SavingMethods saving() const;
    void setSaving(SavingMethods newSaving);
    AudioSamplingRates rate() const;
    void setRate(AudioSamplingRates newRate);

private:
    Commands m_command = StopCommand;
    uint16_t m_time = 0;
    SavingMethods m_saving = RealTimeUpload;
    AudioSamplingRates m_rate = AudioSamplingRate8K;
};

}
#endif // AUDIORECORDINGSTARTCOMMAND_H
