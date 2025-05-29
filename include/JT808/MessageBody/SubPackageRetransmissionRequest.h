#ifndef SUBPACKAGERETRANSMISSIONREQUEST_H
#define SUBPACKAGERETRANSMISSIONREQUEST_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

/**
 * @brief The SubPackageRetransmissionRequest class
 */
class SubPackageRetransmissionRequest : public MessageBodyBase
{
public:
    SubPackageRetransmissionRequest();
    SubPackageRetransmissionRequest(uint16_t seq, const std::vector<uint16_t>& ids);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const SubPackageRetransmissionRequest& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

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
