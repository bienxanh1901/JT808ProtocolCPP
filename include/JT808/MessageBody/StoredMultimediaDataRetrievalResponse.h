#ifndef STOREDMULTIMEDIADATARETRIEVALRESPONSE_H
#define STOREDMULTIMEDIADATARETRIEVALRESPONSE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include "Multimedia.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class StoredMultimediaDataRetrievalResponse : public MessageBodyBase
{
public:
    StoredMultimediaDataRetrievalResponse();
    StoredMultimediaDataRetrievalResponse(uint16_t seq, const std::vector<MultimediaRetrievalData>& result);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const StoredMultimediaDataRetrievalResponse& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    std::vector<MultimediaRetrievalData> result() const;
    void setResult(const std::vector<MultimediaRetrievalData>& newResult);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
    std::vector<MultimediaRetrievalData> m_result;
};

}
#endif // STOREDMULTIMEDIADATARETRIEVALRESPONSE_H
