#ifndef STORAGEMULTIMEDIADATARETRIEVALRESPONSE_H
#define STORAGEMULTIMEDIADATARETRIEVALRESPONSE_H

#include "Multimedia.h"
#include "SequenceMessageBodyBase.h"

namespace JT808::MessageBody {

class StorageMultimediaDataRetrievalResponse : public SequenceMessageBodyBase
{
public:
    StorageMultimediaDataRetrievalResponse() = default;
    StorageMultimediaDataRetrievalResponse(uint16_t seq, const std::vector<MultimediaRetrievalData>& result);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const StorageMultimediaDataRetrievalResponse& other);

    std::vector<MultimediaRetrievalData> result() const;
    void setResult(const std::vector<MultimediaRetrievalData>& newResult);

private:
    std::vector<MultimediaRetrievalData> m_result;
};

}
#endif // STORAGEMULTIMEDIADATARETRIEVALRESPONSE_H
