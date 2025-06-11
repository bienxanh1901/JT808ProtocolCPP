#ifndef MULTIMEDIADATAUPLOAD_H
#define MULTIMEDIADATAUPLOAD_H

#include "BasicLocationInformation.h"
#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include "Multimedia.h"
#include <cstdint>

namespace JT808::MessageBody {

class MultimediaDataUpload : public MessageBodyBase
{
public:
    MultimediaDataUpload();
    MultimediaDataUpload(MultimediaEventInformation info, BasicLocationInformation location, const ByteArray& media);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const MultimediaDataUpload& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    MultimediaEventInformation info() const;
    void setInfo(const MultimediaEventInformation& newInfo);
    BasicLocationInformation location() const;
    void setLocation(const BasicLocationInformation& newLocation);
    ByteArray media() const;
    void setMedia(const ByteArray& newMedia);

private:
    MultimediaEventInformation m_info = {0};
    BasicLocationInformation m_location;
    ByteArray m_media;
};

}
#endif // MULTIMEDIADATAUPLOAD_H
