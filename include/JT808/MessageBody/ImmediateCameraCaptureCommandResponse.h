#ifndef IMMEDIATECAMERACAPTURECOMMANDRESPONSE_H
#define IMMEDIATECAMERACAPTURECOMMANDRESPONSE_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

/**
 * @brief The ImmediateCameraCaptureCommandResponse class
 */
class ImmediateCameraCaptureCommandResponse : public MessageBodyBase
{
public:
    enum ResponseResults : uint8_t
    {
        Succeeded = 0x00,
        Failed = 0x01,
        ChannelNotSupport = 0x02
    };

    ImmediateCameraCaptureCommandResponse();
    ImmediateCameraCaptureCommandResponse(uint16_t seq, ResponseResults result, const std::vector<uint32_t>& ids);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const ImmediateCameraCaptureCommandResponse& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    ResponseResults result() const;
    void setResult(ResponseResults newResult);
    std::vector<uint32_t> ids() const;
    void setIds(const std::vector<uint32_t>& newIds);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
    ResponseResults m_result = Succeeded;
    std::vector<uint32_t> m_ids;
};

}

#endif // IMMEDIATECAMERACAPTURECOMMANDRESPONSE_H
