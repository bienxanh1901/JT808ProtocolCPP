#ifndef QUESTIONRESPONSE_H
#define QUESTIONRESPONSE_H

#include "SequenceMessageBodyBase.h"

namespace JT808::MessageBody {

class QuestionResponse : public SequenceMessageBodyBase
{
public:
    QuestionResponse() = default;
    QuestionResponse(uint16_t seq, uint8_t m_id);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const QuestionResponse& other) const;

    uint8_t id() const;
    void setId(uint8_t newId);

private:
    uint8_t m_id;
};

}
#endif // QUESTIONRESPONSE_H
