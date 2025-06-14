#include "JT808/MessageBody/ImmediateCameraCaptureCommand.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/Multimedia.h"
#include "JT808/Schema/ImmediateCameraCaptureCommandSchema.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

ImmediateCameraCaptureCommand::ImmediateCameraCaptureCommand()
    : MessageBodyBase(Schema::ImmediateCameraCaptureCommandSchema)
{
}

ImmediateCameraCaptureCommand::ImmediateCameraCaptureCommand(uint8_t channel, uint16_t command, uint16_t period,
                                                             SavingMethods saving, Resolutions resolution,
                                                             uint8_t quality, uint8_t brightness, uint8_t contrast,
                                                             uint8_t saturation, uint8_t chroma)
    : MessageBodyBase(Schema::ImmediateCameraCaptureCommandSchema)
    , m_channel(channel)
    , m_command(command)
    , m_period(period)
    , m_saving(saving)
    , m_resolution(resolution)
    , m_quality(quality)
    , m_brightness(brightness)
    , m_contrast(contrast)
    , m_saturation(saturation)
    , m_chroma(chroma)
{
}

void ImmediateCameraCaptureCommand::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void ImmediateCameraCaptureCommand::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;

    // channel
    m_channel = data[pos++];
    // command
    m_command = Utils::endianSwap16(data + pos);
    pos += sizeof(m_command);
    // pediod
    m_period = Utils::endianSwap16(data + pos);
    pos += sizeof(m_period);
    // saving
    m_saving = SavingMethods(data[pos++]);
    // resolution
    m_resolution = Resolutions(data[pos++]);
    // quality
    m_quality = data[pos++];
    // brightness
    m_brightness = data[pos++];
    // contrast
    m_contrast = data[pos++];
    // saturation
    m_saturation = data[pos++];
    // chroma
    m_chroma = data[pos++];

    setIsValid(true);
}

ByteArray ImmediateCameraCaptureCommand::package()
{
    ByteArray result;

    // channel
    result.push_back(m_channel);
    // command
    Utils::appendU16(m_command, result);
    // pediod
    Utils::appendU16(m_period, result);
    // saving
    result.push_back(m_saving);
    // resolution
    result.push_back(m_resolution);
    // quality
    result.push_back(m_quality);
    // brightness
    result.push_back(m_brightness);
    // contrast
    result.push_back(m_contrast);
    // saturation
    result.push_back(m_saturation);
    // chroma
    result.push_back(m_chroma);

    return result;
}

bool ImmediateCameraCaptureCommand::operator==(const ImmediateCameraCaptureCommand& other) const
{
    return m_channel == other.m_channel && m_command == other.m_command && m_period == other.m_period
        && m_saving == other.m_saving && m_resolution == other.m_resolution && m_quality == other.m_quality
        && m_brightness == other.m_brightness && m_contrast == other.m_contrast && m_saturation == other.m_saturation
        && m_chroma == other.m_chroma;
}

void ImmediateCameraCaptureCommand::fromJson(const Json& data)
{
    if (validate(data)) {
        m_channel = data["channel"];
        m_command = data["command"];
        m_period = data["period"];
        m_saving = data["saving"];
        m_resolution = Resolutions(data["resolution"]);
        m_quality = data["quality"];
        m_brightness = data["brightness"];
        m_contrast = data["contrast"];
        m_saturation = data["saturation"];
        m_chroma = data["chroma"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json ImmediateCameraCaptureCommand::toJson()
{
    return Json::object({{"channel", m_channel},
                         {"command", m_command},
                         {"period", m_period},
                         {"saving", m_saving},
                         {"resolution", m_resolution},
                         {"quality", m_quality},
                         {"brightness", m_brightness},
                         {"contrast", m_contrast},
                         {"saturation", m_saturation},
                         {"chroma", m_chroma}});
}

uint8_t ImmediateCameraCaptureCommand::channel() const
{
    return m_channel;
}

void ImmediateCameraCaptureCommand::setchannel(uint8_t newchannel)
{
    m_channel = newchannel;
}

uint16_t ImmediateCameraCaptureCommand::command() const
{
    return m_command;
}

void ImmediateCameraCaptureCommand::setCommand(uint16_t newCommand)
{
    m_command = newCommand;
}

uint16_t ImmediateCameraCaptureCommand::period() const
{
    return m_period;
}

void ImmediateCameraCaptureCommand::setPeriod(uint16_t newPeriod)
{
    m_period = newPeriod;
}

SavingMethods ImmediateCameraCaptureCommand::saving() const
{
    return m_saving;
}

void ImmediateCameraCaptureCommand::setSaving(SavingMethods newSaving)
{
    m_saving = newSaving;
}

ImmediateCameraCaptureCommand::Resolutions ImmediateCameraCaptureCommand::resolution() const
{
    return m_resolution;
}

void ImmediateCameraCaptureCommand::setResolution(Resolutions newResolution)
{
    m_resolution = newResolution;
}

uint8_t ImmediateCameraCaptureCommand::quality() const
{
    return m_quality;
}

void ImmediateCameraCaptureCommand::setQuality(uint8_t newQuality)
{
    m_quality = newQuality;
}

uint8_t ImmediateCameraCaptureCommand::brightness() const
{
    return m_brightness;
}

void ImmediateCameraCaptureCommand::setBrightness(uint8_t newBrightness)
{
    m_brightness = newBrightness;
}

uint8_t ImmediateCameraCaptureCommand::contrast() const
{
    return m_contrast;
}

void ImmediateCameraCaptureCommand::setContrast(uint8_t newContrast)
{
    m_contrast = newContrast;
}

uint8_t ImmediateCameraCaptureCommand::saturation() const
{
    return m_saturation;
}

void ImmediateCameraCaptureCommand::setSaturation(uint8_t newSaturation)
{
    m_saturation = newSaturation;
}

uint8_t ImmediateCameraCaptureCommand::chroma() const
{
    return m_chroma;
}

void ImmediateCameraCaptureCommand::setChroma(uint8_t newChroma)
{
    m_chroma = newChroma;
}

}
