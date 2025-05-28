#include "JT808/MessageBody/AudioRecordingStartCommand.h"

namespace JT808::MessageBody {

AudioRecordingStartCommand::AudioRecordingStartCommand(Commands command, uint16_t time, SavingMethods saving,
                                                       AudioSamplingRates rate)
    : MessageBodyBase()
    , m_command(command)
    , m_time(time)
    , m_saving(saving)
    , m_rate(rate)
{
}

void AudioRecordingStartCommand::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void AudioRecordingStartCommand::parse(const uint8_t* data, int size)
{
    int pos = 0;

    // command
    m_command = Commands(data[pos++]);
    // time
    m_time = Utils::endianSwap16(data + pos);
    pos += sizeof(m_time);
    // saving
    m_saving = SavingMethods(data[pos++]);
    // sampling rate
    m_rate = AudioSamplingRates(data[pos++]);

    setIsValid(true);
}

std::vector<uint8_t> AudioRecordingStartCommand::package()
{
    std::vector<uint8_t> result;

    // command
    result.push_back(m_command);
    // time
    Utils::appendU16(m_time, result);
    // saving
    result.push_back(m_saving);
    // sampling rate
    result.push_back(m_rate);

    return result;
}

bool AudioRecordingStartCommand::operator==(const AudioRecordingStartCommand& other) const
{
    return m_command == other.m_command && m_time == other.m_time && m_saving == other.m_saving
        && m_rate == other.m_rate;
}

AudioRecordingStartCommand::Commands AudioRecordingStartCommand::command() const
{
    return m_command;
}

void AudioRecordingStartCommand::setCommand(Commands newCommand)
{
    m_command = newCommand;
}

uint16_t AudioRecordingStartCommand::time() const
{
    return m_time;
}

void AudioRecordingStartCommand::setTime(uint16_t newTime)
{
    m_time = newTime;
}

SavingMethods AudioRecordingStartCommand::saving() const
{
    return m_saving;
}

void AudioRecordingStartCommand::setSaving(SavingMethods newSaving)
{
    m_saving = newSaving;
}

AudioRecordingStartCommand::AudioSamplingRates AudioRecordingStartCommand::rate() const
{
    return m_rate;
}

void AudioRecordingStartCommand::setRate(AudioSamplingRates newRate)
{
    m_rate = newRate;
}

}
