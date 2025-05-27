#include "JT808/MessageBody/Multimedia.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

bool MultimediaEventInformation::operator==(const MultimediaEventInformation& other) const
{
    return id == other.id && type == other.type && format == other.format && event == other.event
        && channel == other.channel;
}

void MultimediaEventInformation::parse(const uint8_t* data, int size)
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

std::vector<uint8_t> MultimediaEventInformation::package()
{
    std::vector<uint8_t> result;

    Utils::appendU32(id, result);
    result.push_back(type);
    result.push_back(format);
    result.push_back(event);
    result.push_back(channel);

    return result;
}

bool MultimediaRetrievalData::operator==(const MultimediaRetrievalData& other) const
{
    return id == other.id && type == other.type && event == other.event && channel == other.channel
        && location == other.location;
}

void MultimediaRetrievalData::parse(const uint8_t* data, int size)
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
    std::vector<uint8_t> locationData(location.package());
    std::vector<uint8_t> result;

    Utils::appendU32(id, result);
    result.push_back(type);
    result.push_back(channel);
    result.push_back(event);
    result.insert(result.end(), locationData.begin(), locationData.end());

    return result;
}

}
