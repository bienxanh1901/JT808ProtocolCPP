#ifndef QUESTIONRESPONSE_H
#define QUESTIONRESPONSE_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class QuestionResponse : public MessageBodyBase
{
public:
    QuestionResponse();
    QuestionResponse(uint16_t seq, uint8_t m_id);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const QuestionResponse& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

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
