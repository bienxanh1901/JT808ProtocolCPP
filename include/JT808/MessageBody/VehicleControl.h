#ifndef VEHICLECONTROL_H
#define VEHICLECONTROL_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

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

    VehicleControl() = default;
    VehicleControl(Flag flag);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const VehicleControl& other) const;

    Flag flag() const;
    void setFlag(const Flag& newFlag);

private:
    Flag m_flag = {0};
};

}
#endif // VEHICLECONTROL_H
