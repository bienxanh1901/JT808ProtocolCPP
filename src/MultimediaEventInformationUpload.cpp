#include "JT808/MessageBody/MultimediaEventInformationUpload.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/Multimedia.h"
#include "JT808/Schema/MultimediaEventInformationUploadSchema.h"
#include <cstdint>

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

void MultimediaEventInformationUpload::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void MultimediaEventInformationUpload::parse(const uint8_t* data, int size)
{
    m_info.parse(data, size);

    setIsValid(true);
}

ByteArray MultimediaEventInformationUpload::package()
{
    return m_info.package();
}

bool MultimediaEventInformationUpload::operator==(const MultimediaEventInformationUpload& other) const
{
    return m_info == other.m_info;
}

void MultimediaEventInformationUpload::fromJson(const Json& data)
{
    if (validate(data)) {
        m_info.fromJson(data);
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json MultimediaEventInformationUpload::toJson()
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
