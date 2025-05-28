#ifndef IMMEDIATECAMERACAPTURECOMMAND_H
#define IMMEDIATECAMERACAPTURECOMMAND_H

#include "MessageBodyBase.h"
#include "Multimedia.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class ImmediateCameraCaptureCommand : public MessageBodyBase
{
public:
    enum Resolutions : uint8_t
    {
        Resolution320x240 = 0x01,
        Resolution640x480 = 0x02,
        Resolution800x600 = 0x03,
        Resolution1024x768 = 0x04,
        Resolution176x144 = 0x05,
        Resolution352x288 = 0x06,
        Resolution704x288 = 0x07,
        Resolution704x576 = 0x08,
    };

    ImmediateCameraCaptureCommand() = default;
    ImmediateCameraCaptureCommand(uint8_t channel, uint16_t command, uint16_t period, SavingMethods saving,
                                  Resolutions resolution, uint8_t quality, uint8_t brightness, uint8_t contrast,
                                  uint8_t saturation, uint8_t chroma);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const ImmediateCameraCaptureCommand& other) const;

    uint8_t channel() const;
    void setchannel(uint8_t newchannel);
    uint16_t command() const;
    void setCommand(uint16_t newCommand);
    uint16_t period() const;
    void setPeriod(uint16_t newPeriod);
    SavingMethods saving() const;
    void setSaving(SavingMethods newSaving);
    Resolutions resolution() const;
    void setResolution(Resolutions newResolution);
    uint8_t quality() const;
    void setQuality(uint8_t newQuality);
    uint8_t brightness() const;
    void setBrightness(uint8_t newBrightness);
    uint8_t contrast() const;
    void setContrast(uint8_t newContrast);
    uint8_t saturation() const;
    void setSaturation(uint8_t newSaturation);
    uint8_t chroma() const;
    void setChroma(uint8_t newChroma);

private:
    uint8_t m_channel = 0;
    uint16_t m_command = 0;
    uint16_t m_period = 0;
    SavingMethods m_saving = RealTimeUpload;
    Resolutions m_resolution = Resolution320x240;
    uint8_t m_quality = 1;
    uint8_t m_brightness = 0;
    uint8_t m_contrast = 0;
    uint8_t m_saturation = 0;
    uint8_t m_chroma = 0;
};

}
#endif // IMMEDIATECAMERACAPTURECOMMAND_H
