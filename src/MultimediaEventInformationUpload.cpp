#include "JT808/MessageBody/MultimediaEventInformationUpload.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/Multimedia.h"
#include "JT808/Schema/MultimediaEventInformationUploadSchema.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

MultimediaEventInformationUpload::MultimediaEventInformationUpload()
    : MessageBodyBase(Schema::MultimediaEventInformationUploadSchema)
{
}

MultimediaEventInformationUpload::MultimediaEventInformationUpload(MultimediaEventInformation info)
    : MessageBodyBase(Schema::MultimediaEventInformationUploadSchema)
    , m_info(info)
{
}

void MultimediaEventInformationUpload::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void MultimediaEventInformationUpload::parse(const uint8_t* data, int size)
{
    m_info.parse(data, size);

    setIsValid(true);
}

std::vector<uint8_t> MultimediaEventInformationUpload::package()
{
    return m_info.package();
}

bool MultimediaEventInformationUpload::operator==(const MultimediaEventInformationUpload& other) const
{
    return m_info == other.m_info;
}

void MultimediaEventInformationUpload::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_info.fromJson(data);
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json MultimediaEventInformationUpload::toJson()
{
    return m_info.toJson();
}

MultimediaEventInformation MultimediaEventInformationUpload::info() const
{
    return m_info;
}

void MultimediaEventInformationUpload::setInfo(const MultimediaEventInformation& newInfo)
{
    m_info = newInfo;
}

}
