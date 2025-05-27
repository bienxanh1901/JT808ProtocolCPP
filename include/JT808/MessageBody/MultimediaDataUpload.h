#ifndef MULTIMEDIADATAUPLOAD_H
#define MULTIMEDIADATAUPLOAD_H

#include "LocationInformation.h"
#include "MessageBodyBase.h"
#include "Multimedia.h"

namespace JT808::MessageBody {

class MultimediaDataUpload : public MessageBodyBase
{
public:
    MultimediaDataUpload() = default;
    MultimediaDataUpload(MultimediaEventInformation info, LocationInformation location, const std::string& media);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const MultimediaDataUpload& other);

    MultimediaEventInformation info() const;
    void setInfo(const MultimediaEventInformation& newInfo);
    LocationInformation location() const;
    void setLocation(const LocationInformation& newLocation);
    std::string media() const;
    void setMedia(const std::string& newMedia);

private:
    MultimediaEventInformation m_info = {0};
    LocationInformation m_location;
    std::string m_media;
};

}
#endif // MULTIMEDIADATAUPLOAD_H
