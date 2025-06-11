#ifndef QUESTIONRESPONSE_H
#define QUESTIONRESPONSE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class QuestionResponse : public MessageBodyBase
{
public:
    QuestionResponse();
    QuestionResponse(uint16_t seq, uint8_t m_id);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const QuestionResponse& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint8_t id() const;
    void setId(uint8_t newId);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq;
    uint8_t m_id;
};

}
#endif // QUESTIONRESPONSE_H
