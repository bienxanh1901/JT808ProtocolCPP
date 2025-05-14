#ifndef MANUALALARMCONFIRMATION_H
#define MANUALALARMCONFIRMATION_H

#include "MessageBodyBase.h"

#include <stdint.h>

namespace JT808 {
namespace MessageBody {

typedef union {
    struct
    {
        uint32_t sos : 1;
        uint32_t reserved : 2;
        uint32_t alert : 1;
        uint32_t reserved2 : 16;
        uint32_t inOutArea : 1;
        uint32_t inOutRoute : 1;
        uint32_t routeDrivingTime : 1;
        uint32_t reserved3 : 4;
        uint32_t acc : 1;
        uint32_t move : 1;
        uint32_t reserved4 : 3;
    } bits;
    uint32_t value;
} ManualAlarmConfirmationTypes;

class ManualAlarmConfirmation : public MessageBodyBase
{
public:
    ManualAlarmConfirmation(const std::vector<uint8_t>& data = {});
    ManualAlarmConfirmation(uint8_t* data, int size);

    void parse() override;
    void package() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);
    ManualAlarmConfirmationTypes type() const;
    void setType(const ManualAlarmConfirmationTypes& newType);

private:
    uint16_t m_seq;
    ManualAlarmConfirmationTypes m_type;
};

}
}

#endif // MANUALALARMCONFIRMATION_H
