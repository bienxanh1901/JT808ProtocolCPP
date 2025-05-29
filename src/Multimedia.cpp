#include "JT808/MessageBody/Multimedia.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

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

std::vector<uint8_t> MultimediaEventInformation::package() const
{
    std::vector<uint8_t> result;
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

void MultimediaEventInformation::fromJson(const nlohmann::json& data)
{
    id = data["id"];
    type = data["type"];
    format = data["format"];
    event = data["event"];
    channel = data["channel"];
}

nlohmann::json MultimediaEventInformation::toJson()
{
    return {
        {"id", id}, {"type", type}, {"format", format}, {"event", event}, {"channel", channel},
    };
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

std::vector<uint8_t> MultimediaRetrievalData::package()
{
    std::vector<uint8_t> result;
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

void MultimediaRetrievalData::fromJson(const nlohmann::json& data)
{
    id = data["id"];
    type = data["type"];
    event = data["event"];
    channel = data["channel"];
    location.fromJson(data["location"]);
}

nlohmann::json MultimediaRetrievalData::toJson()
{
    return nlohmann::json::object({
        {"id", id},
        {"type", type},
        {"event", event},
        {"channel", channel},
        {"location", location.toJson()},
    });
}

}
