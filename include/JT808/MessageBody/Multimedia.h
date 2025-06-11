#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include "BasicLocationInformation.h"
#include "JT808/Common.h"
#include <cstdint>

namespace JT808::MessageBody {

enum SavingMethods : uint8_t
{
    RealTimeUpload = 0,
    LocalStorage = 1
};

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

    bool operator==(const MultimediaEventInformation& other) const;
    void parse(const uint8_t* data, int size);
    ByteArray package() const;

    void fromJson(const Json& data);
    Json toJson();
};

struct MultimediaRetrievalData
{
    uint32_t id = 0;
    MediaType type = ImageType;
    uint8_t channel = 0;
    EventCode event = PlaformCommand;
    BasicLocationInformation location;

    bool operator==(const MultimediaRetrievalData& other) const;
    void parse(const uint8_t* data, int size);
    ByteArray package();

    void fromJson(const Json& data);
    Json toJson();
};

}
#endif // MULTIMEDIA_H
