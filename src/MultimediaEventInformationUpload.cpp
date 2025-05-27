#include "JT808/MessageBody/MultimediaEventInformationUpload.h"

namespace JT808::MessageBody {

MultimediaEventInformationUpload::MultimediaEventInformationUpload(MultimediaEventInformation info)
    : MessageBodyBase()
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

bool MultimediaEventInformationUpload::operator==(const MultimediaEventInformationUpload& other)
{
    return m_info == other.m_info;
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
