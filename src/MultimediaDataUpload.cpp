#include "JT808/MessageBody/MultimediaDataUpload.h"

namespace JT808::MessageBody {

MultimediaDataUpload::MultimediaDataUpload(MultimediaEventInformation info, LocationInformation location,
                                           const std::string& media)
    : MessageBodyBase()
    , m_info(info)
    , m_location(std::move(location))
    , m_media(media)
{
}

void MultimediaDataUpload::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void MultimediaDataUpload::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // info
    m_info.parse(data, sizeof(m_info));
    pos += sizeof(m_info);
    // location
    m_location.parse(data + pos, 28);
    pos += 28;
    // media
    m_media.assign(data + pos, data + size);

    setIsValid(true);
}

std::vector<uint8_t> MultimediaDataUpload::package()
{
    // info
    std::vector<uint8_t> result(m_info.package());
    // location
    Utils::append(m_location.package(), result);
    // media
    Utils::append(m_media, result);

    return result;
}

bool MultimediaDataUpload::operator==(const MultimediaDataUpload& other) const
{
    return m_info == other.m_info && m_location == other.m_location && m_media == other.m_media;
}

MultimediaEventInformation MultimediaDataUpload::info() const
{
    return m_info;
}

void MultimediaDataUpload::setInfo(const MultimediaEventInformation& newInfo)
{
    m_info = newInfo;
}

LocationInformation MultimediaDataUpload::location() const
{
    return m_location;
}

void MultimediaDataUpload::setLocation(const LocationInformation& newLocation)
{
    m_location = newLocation;
}

std::string MultimediaDataUpload::media() const
{
    return m_media;
}

void MultimediaDataUpload::setMedia(const std::string& newMedia)
{
    m_media = newMedia;
}

}
