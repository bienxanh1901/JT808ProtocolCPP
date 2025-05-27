#ifndef MULTIMEDIAEVENTINFORMATION_H
#define MULTIMEDIAEVENTINFORMATION_H

#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

enum MediaType : uint8_t
{
    ImageType = 0,
    AudioType,
    VideoType
};

enum MediaFormat : uint8_t
{
    JPEGFormat = 0,
    TIFFormat,
    MP3Format,
    WAVFormat,
    WMVFormat,
    OtherFormat
};

enum EventCode : uint8_t
{
    PlaformCommand = 0,
    TimerEvent,
    ThreatAlarmTrigger,
    CollisionRolloverAlarmTrigger,
    DoorOpenedImage,
    DoorClosedImage,
    DoorClosing,
    FixedDistanceImage
};

struct MultimediaEventInformation
{
    uint32_t id = 0;
    MediaType type = ImageType;
    MediaFormat format = OtherFormat;
    EventCode event = PlaformCommand;
    uint8_t channel = 0;

    bool operator==(const MultimediaEventInformation& other) const
    {
        return id == other.id && type == other.type && format == other.format && event == other.event
            && channel == other.channel;
    }

    void parse(const uint8_t* data, int size)
    {
        int pos = 0;
        // id
        id = Utils::endianSwap32(data);
        pos += sizeof(id);
        // type
        type = MediaType(data[pos++]);
        // format
        format = MediaFormat(data[pos++]);
        // event
        event = EventCode(data[pos++]);
        // channel
        channel = MediaType(data[pos]);
    }

    std::vector<uint8_t> package()
    {
        std::vector<uint8_t> result;

        Utils::appendU32(id, result);
        result.push_back(type);
        result.push_back(format);
        result.push_back(event);
        result.push_back(channel);

        return result;
    }
};
}
#endif // MULTIMEDIAEVENTINFORMATION_H
