#include "JT808/MessageBody/MultimediaDataUpload.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/Multimedia.h"
#include "JT808/Schema/MultimediaDataUploadSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

MultimediaDataUpload::MultimediaDataUpload()
    : MessageBodyBase(Schema::MultimediaDataUploadSchema)
{
}

MultimediaDataUpload::MultimediaDataUpload(MultimediaEventInformation info, BasicLocationInformation location,
                                           const std::vector<uint8_t>& media)
    : MessageBodyBase(Schema::MultimediaDataUploadSchema)
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

void MultimediaDataUpload::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_info.fromJson(data["info"]);
        m_location.fromJson(data["location"]);
        m_media = data["multimedia"].get<std::vector<uint8_t>>();
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json MultimediaDataUpload::toJson()
{
    nlohmann::json result;
    result["info"] = m_info.toJson();
    result["location"] = m_location.toJson();
    result["multimedia"] = m_media;
    return result;
}

MultimediaEventInformation MultimediaDataUpload::info() const
{
    return m_info;
}

void MultimediaDataUpload::setInfo(const MultimediaEventInformation& newInfo)
{
    m_info = newInfo;
}

BasicLocationInformation MultimediaDataUpload::location() const
{
    return m_location;
}

void MultimediaDataUpload::setLocation(const BasicLocationInformation& newLocation)
{
    m_location = newLocation;
}

std::vector<uint8_t> MultimediaDataUpload::media() const
{
    return m_media;
}

void MultimediaDataUpload::setMedia(const std::vector<uint8_t>& newMedia)
{
    m_media = newMedia;
}

}
