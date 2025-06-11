#ifndef MULTIMEDIAEVENTINFORMATIONUPLOAD_H
#define MULTIMEDIAEVENTINFORMATIONUPLOAD_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include "Multimedia.h"
#include <cstdint>

namespace JT808::MessageBody {

class MultimediaEventInformationUpload : public MessageBodyBase
{
public:
    MultimediaEventInformationUpload();
    MultimediaEventInformationUpload(MultimediaEventInformation info);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const MultimediaEventInformationUpload& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    MultimediaEventInformation info() const;
    void setInfo(const MultimediaEventInformation& newInfo);

private:
    MultimediaEventInformation m_info = {};
};

}
#endif // MULTIMEDIAEVENTINFORMATIONUPLOAD_H
