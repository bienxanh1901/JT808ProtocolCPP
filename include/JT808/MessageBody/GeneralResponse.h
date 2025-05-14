#ifndef GENERALRESPONSE_H
#define GENERALRESPONSE_H

#include "MessageBodyBase.h"
#include <stdint.h>

namespace JT808 {
namespace MessageBody {

/**
 * @brief The GeneralResponse class
 */
class GeneralResponse : public MessageBodyBase
{
public:
    typedef enum
    {
        Succeeded = 0x00,
        Failed = 0x01,
        IncorrectInformation = 0x02,
        NotSupporting = 0x03,
        AlarmProcessingConfirmation = 0x04,
    } ResponseResults;

    GeneralResponse(const std::vector<uint8_t>& data = {});
    GeneralResponse(uint8_t* data, int size);

    void parse() override;
    void package() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

    uint16_t id() const;
    void setId(uint16_t newId);

    ResponseResults result() const;
    void setResult(ResponseResults newResult);

private:
    int m_expectedSize = 5;
    uint16_t m_seq = 0;
    uint16_t m_id = 0;
    ResponseResults m_result = Succeeded;
};

}
}

#endif // GENERALRESPONSE_H
