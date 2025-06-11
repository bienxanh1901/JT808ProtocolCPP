#ifndef VEHICLECONTROL_H
#define VEHICLECONTROL_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class VehicleControl : public MessageBodyBase
{
public:
    union Flag {
        struct
        {
            uint8_t doorLocked : 1;
            uint8_t reserved : 7;
        } bits;
        uint8_t value = 0;
    };

    VehicleControl();
    VehicleControl(Flag flag);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const VehicleControl& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    Flag flag() const;
    void setFlag(const Flag& newFlag);

private:
    Flag m_flag = {0};
};

}
#endif // VEHICLECONTROL_H
