#ifndef IMMEDIATECAMERACAPTURECOMMANDRESPONSE_H
#define IMMEDIATECAMERACAPTURECOMMANDRESPONSE_H

#include "SequenceMessageBodyBase.h"

namespace JT808::MessageBody {

/**
 * @brief The ImmediateCameraCaptureCommandResponse class
 */
class ImmediateCameraCaptureCommandResponse : public SequenceMessageBodyBase
{
public:
    enum ResponseResults : uint8_t
    {
        Succeeded = 0x00,
        Failed = 0x01,
        ChannelNotSupport = 0x02
    };

    ImmediateCameraCaptureCommandResponse() = default;
    ImmediateCameraCaptureCommandResponse(uint16_t seq, ResponseResults result, const std::vector<uint32_t>& ids);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const ImmediateCameraCaptureCommandResponse& other);

    ResponseResults result() const;
    void setResult(ResponseResults newResult);
    uint16_t length() const;
    void setLength(uint16_t newLength);
    std::vector<uint32_t> ids() const;
    void setIds(const std::vector<uint32_t>& newIds);

private:
    ResponseResults m_result = Succeeded;
    uint16_t m_length = 0;
    std::vector<uint32_t> m_ids;
};

}

#endif // IMMEDIATECAMERACAPTURECOMMANDRESPONSE_H
