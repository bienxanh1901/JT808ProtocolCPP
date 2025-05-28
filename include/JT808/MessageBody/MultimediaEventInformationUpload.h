#ifndef MULTIMEDIAEVENTINFORMATIONUPLOAD_H
#define MULTIMEDIAEVENTINFORMATIONUPLOAD_H

#include "MessageBodyBase.h"
#include "Multimedia.h"

namespace JT808::MessageBody {

class MultimediaEventInformationUpload : public MessageBodyBase
{
public:
    MultimediaEventInformationUpload() = default;
    MultimediaEventInformationUpload(MultimediaEventInformation info);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const MultimediaEventInformationUpload& other) const;

    MultimediaEventInformation info() const;
    void setInfo(const MultimediaEventInformation& newInfo);

private:
    MultimediaEventInformation m_info = {};
};

}
#endif // MULTIMEDIAEVENTINFORMATIONUPLOAD_H
