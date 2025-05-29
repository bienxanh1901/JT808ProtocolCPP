#ifndef MULTIMEDIADATAUPLOAD_H
#define MULTIMEDIADATAUPLOAD_H

#include "BasicLocationInformation.h"
#include "MessageBodyBase.h"
#include "Multimedia.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class MultimediaDataUpload : public MessageBodyBase
{
public:
    MultimediaDataUpload();
    MultimediaDataUpload(MultimediaEventInformation info, BasicLocationInformation location,
                         const std::vector<uint8_t>& media);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const MultimediaDataUpload& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    MultimediaEventInformation info() const;
    void setInfo(const MultimediaEventInformation& newInfo);
    BasicLocationInformation location() const;
    void setLocation(const BasicLocationInformation& newLocation);
    std::vector<uint8_t> media() const;
    void setMedia(const std::vector<uint8_t>& newMedia);

private:
    MultimediaEventInformation m_info = {0};
    BasicLocationInformation m_location;
    std::vector<uint8_t> m_media;
};

}
#endif // MULTIMEDIADATAUPLOAD_H
