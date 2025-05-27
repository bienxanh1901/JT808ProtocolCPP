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

    m_info.parse(data, sizeof(m_info));
    pos += sizeof(m_info);
    m_location.parse(data + pos, 28);
    pos += 28;
    m_media.assign(data + pos, data + size);

    setIsValid(true);
}

std::vector<uint8_t> MultimediaDataUpload::package()
{
    std::vector<uint8_t> locationData(m_location.package());
    std::vector<uint8_t> result(m_info.package());

    result.insert(result.end(), locationData.begin(), locationData.end());
    result.insert(result.end(), m_media.begin(), m_media.end());

    return result;
}

bool MultimediaDataUpload::operator==(const MultimediaDataUpload& other)
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
