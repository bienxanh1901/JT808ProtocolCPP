#ifndef SUBPACKAGERETRANSMISSIONREQUEST_H
#define SUBPACKAGERETRANSMISSIONREQUEST_H

#include "MessageBodyBase.h"
#include <stdint.h>
#include <vector>

namespace JT808 {
namespace MessageBody {

/**
 * @brief The SubPackageRetransmissionRequest class
 */
class SubPackageRetransmissionRequest : public MessageBodyBase
{
public:
    SubPackageRetransmissionRequest(const std::vector<uint8_t>& data = {});
    SubPackageRetransmissionRequest(uint8_t* data, int size);

    void parse() override;
    void package() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

    uint8_t length() const;
    void setLength(uint8_t newLength);

    std::vector<uint16_t> ids() const;
    void setIds(const std::vector<uint16_t>& newIds);

private:
    uint16_t m_seq = 0;
    uint8_t m_length = 0;
    std::vector<uint16_t> m_ids = {};
};

}
}

#endif // SUBPACKAGERETRANSMISSIONREQUEST_H
