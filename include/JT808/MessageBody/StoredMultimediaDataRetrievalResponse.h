#ifndef STOREDMULTIMEDIADATARETRIEVALRESPONSE_H
#define STOREDMULTIMEDIADATARETRIEVALRESPONSE_H

#include "MessageBodyBase.h"
#include "Multimedia.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class StoredMultimediaDataRetrievalResponse : public MessageBodyBase
{
public:
    StoredMultimediaDataRetrievalResponse();
    StoredMultimediaDataRetrievalResponse(uint16_t seq, const std::vector<MultimediaRetrievalData>& result);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const StoredMultimediaDataRetrievalResponse& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

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
