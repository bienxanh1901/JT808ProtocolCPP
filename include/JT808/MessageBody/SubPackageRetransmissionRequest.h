#ifndef SUBPACKAGERETRANSMISSIONREQUEST_H
#define SUBPACKAGERETRANSMISSIONREQUEST_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

/**
 * @brief The SubPackageRetransmissionRequest class
 */
class SubPackageRetransmissionRequest : public MessageBodyBase
{
public:
    SubPackageRetransmissionRequest();
    SubPackageRetransmissionRequest(uint16_t seq, const std::vector<uint16_t>& ids);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const SubPackageRetransmissionRequest& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    std::vector<uint16_t> ids() const;
    void setIds(const std::vector<uint16_t>& newIds);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
    std::vector<uint16_t> m_ids;
};

}

#endif // SUBPACKAGERETRANSMISSIONREQUEST_H
