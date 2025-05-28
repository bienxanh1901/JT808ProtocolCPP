#ifndef SEQUENCEMESSAGEBODYBASE_H
#define SEQUENCEMESSAGEBODYBASE_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

/**
 * @brief The ResponseMessageBodyBase class
 */
class SequenceMessageBodyBase : public MessageBodyBase
{
public:
    SequenceMessageBodyBase() = default;
    SequenceMessageBodyBase(uint16_t seq);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const SequenceMessageBodyBase& other) const;
    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
};

}

#endif // SEQUENCEMESSAGEBODYBASE_H
