#ifndef GENERALRESPONSE_H
#define GENERALRESPONSE_H

#include "SequenceMessageBodyBase.h"

namespace JT808::MessageBody {

/**
 * @brief The GeneralResponse class
 */
class GeneralResponse : public SequenceMessageBodyBase
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

    GeneralResponse() = default;
    GeneralResponse(uint16_t seq, uint16_t id, ResponseResults result);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const GeneralResponse& other) const;

    uint16_t id() const;
    void setId(uint16_t newId);

    ResponseResults result() const;
    void setResult(ResponseResults newResult);

private:
    uint16_t m_id = 0;
    ResponseResults m_result = Succeeded;
};

}

#endif // GENERALRESPONSE_H
