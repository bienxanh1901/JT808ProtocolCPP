#ifndef SUBPACKAGERETRANSMISSIONREQUEST_H
#define SUBPACKAGERETRANSMISSIONREQUEST_H

#include "SequenceMessageBodyBase.h"

namespace JT808::MessageBody {

/**
 * @brief The SubPackageRetransmissionRequest class
 */
class SubPackageRetransmissionRequest : public SequenceMessageBodyBase
{
public:
    SubPackageRetransmissionRequest() = default;
    SubPackageRetransmissionRequest(uint16_t seq, const std::vector<uint16_t>& ids);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const SubPackageRetransmissionRequest& other);

    uint8_t length() const;
    void setLength(uint8_t newLength);

    std::vector<uint16_t> ids() const;
    void setIds(const std::vector<uint16_t>& newIds);

private:
    uint8_t m_length = 0;
    std::vector<uint16_t> m_ids;
};

}

#endif // SUBPACKAGERETRANSMISSIONREQUEST_H
