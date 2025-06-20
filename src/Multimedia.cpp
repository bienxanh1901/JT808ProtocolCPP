#include "JT808/MessageBody/Multimedia.h"
#include "JT808/Common.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

MultimediaEventInformation::MultimediaEventInformation(const uint8_t* data, int size)
{
    parse(data, size);
}

MultimediaEventInformation::MultimediaEventInformation(const Json& data)
{
    fromJson(data);
}

MultimediaEventInformation::MultimediaEventInformation(uint32_t id, MediaType type, MediaFormat format, EventCode event,
                                                       uint8_t channel)
    : id(id)
    , type(type)
    , format(format)
    , event(event)
    , channel(channel)
{
}

bool MultimediaEventInformation::operator==(const MultimediaEventInformation& other) const
{
    return id == other.id && type == other.type && format == other.format && event == other.event
        && channel == other.channel;
}

void MultimediaEventInformation::parse(const uint8_t* data, int /*size*/)
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

ByteArray MultimediaEventInformation::package() const
{
    ByteArray result;
    // id
    Utils::appendU32(id, result);
    // type
    result.push_back(type);
    // format
    result.push_back(format);
    // event
    result.push_back(event);
    // channel
    result.push_back(channel);

    return result;
}

void MultimediaEventInformation::fromJson(const Json& data)
{
    id = data["id"];
    type = data["type"];
    format = data["format"];
    event = data["event"];
    channel = data["channel"];
}

Json MultimediaEventInformation::toJson()
{
    return {
        {"id", id}, {"type", type}, {"format", format}, {"event", event}, {"channel", channel},
    };
}

MultimediaRetrievalData::MultimediaRetrievalData(const uint8_t* data, int size)
{
    parse(data, size);
}

MultimediaRetrievalData::MultimediaRetrievalData(const Json& data)
{
    fromJson(data);
}

MultimediaRetrievalData::MultimediaRetrievalData(uint32_t id, MediaType type, uint8_t channel, EventCode event,
                                                 BasicLocationInformation location)
    : id(id)
    , type(type)
    , channel(channel)
    , event(event)
    , location(location)
{
}

bool MultimediaRetrievalData::operator==(const MultimediaRetrievalData& other) const
{
    return id == other.id && type == other.type && event == other.event && channel == other.channel
        && location == other.location;
}

void MultimediaRetrievalData::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    // id
    id = Utils::endianSwap32(data);
    pos += sizeof(id);
    // type
    type = MediaType(data[pos++]);
    // channel
    channel = MediaType(data[pos++]);
    // event
    event = EventCode(data[pos++]);
    // location
    location.parse(data + pos, 28);
}

ByteArray MultimediaRetrievalData::package()
{
    ByteArray result;
    // id
    Utils::appendU32(id, result);
    // type
    result.push_back(type);
    // channel
    result.push_back(channel);
    // event
    result.push_back(event);
    // location
    Utils::append(location.package(), result);

    return result;
}

void MultimediaRetrievalData::fromJson(const Json& data)
{
    id = data["id"];
    type = data["type"];
    event = data["event"];
    channel = data["channel"];
    location.fromJson(data["location"]);
}

Json MultimediaRetrievalData::toJson()
{
    return Json::object({
        {"id", id},
        {"type", type},
        {"event", event},
        {"channel", channel},
        {"location", location.toJson()},
    });
}

}
