#ifndef MANUALALARMCONFIRMATION_H
#define MANUALALARMCONFIRMATION_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

union ManualAlarmConfirmationTypes {
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
    uint32_t value = 0;
};

class ManualAlarmConfirmation : public MessageBodyBase
{
public:
    ManualAlarmConfirmation();
    ManualAlarmConfirmation(uint16_t seq, ManualAlarmConfirmationTypes type);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const ManualAlarmConfirmation& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    ManualAlarmConfirmationTypes type() const;
    void setType(const ManualAlarmConfirmationTypes& newType);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
    ManualAlarmConfirmationTypes m_type = {0};
};

}

#endif // MANUALALARMCONFIRMATION_H
