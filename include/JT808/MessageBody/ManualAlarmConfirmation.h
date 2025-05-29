#ifndef MANUALALARMCONFIRMATION_H
#define MANUALALARMCONFIRMATION_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

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
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const ManualAlarmConfirmation& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

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
