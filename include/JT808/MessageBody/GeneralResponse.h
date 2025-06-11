#ifndef GENERALRESPONSE_H
#define GENERALRESPONSE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

/**
 * @brief The GeneralResponse class
 */
class GeneralResponse : public MessageBodyBase
{
public:
    enum ResponseResults : uint8_t
    {
        Succeeded = 0x00,
        Failed = 0x01,
        IncorrectInformation = 0x02,
        NotSupporting = 0x03,
        AlarmProcessingConfirmation = 0x04,
    };

    GeneralResponse();
    GeneralResponse(uint16_t seq, uint16_t id, ResponseResults result);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const GeneralResponse& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint16_t id() const;
    void setId(uint16_t newId);

    ResponseResults result() const;
    void setResult(ResponseResults newResult);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
    uint16_t m_id = 0;
    ResponseResults m_result = Succeeded;
};

}

#endif // GENERALRESPONSE_H
