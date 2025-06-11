#ifndef MULTIMEDIADATAUPLOADRESPONSE_H
#define MULTIMEDIADATAUPLOADRESPONSE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

/**
 * @brief The MultimediaDataUploadResponse class
 */
class MultimediaDataUploadResponse : public MessageBodyBase
{
public:
    MultimediaDataUploadResponse();
    MultimediaDataUploadResponse(uint32_t id, std::vector<uint16_t>& retxIds);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const MultimediaDataUploadResponse& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint16_t id() const;
    void setId(uint16_t newId);

    std::vector<uint16_t> retxIds() const;
    void setRetxIds(const std::vector<uint16_t>& newRetxIds);

private:
    uint32_t m_id = 0;
    std::vector<uint16_t> m_retxIds;
};

}

#endif // MULTIMEDIADATAUPLOADRESPONSE_H
