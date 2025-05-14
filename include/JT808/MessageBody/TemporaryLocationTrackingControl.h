#ifndef TEMPORARYLOCATIONTRACKINGCONTROL_H
#define TEMPORARYLOCATIONTRACKINGCONTROL_H

#include "MessageBodyBase.h"

#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class TemporaryLocationTrackingControl : public MessageBodyBase
{
public:
    TemporaryLocationTrackingControl() = default;
    TemporaryLocationTrackingControl(uint16_t period, uint32_t expiry);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TemporaryLocationTrackingControl& other);

    uint16_t period() const;
    void setPeriod(uint16_t newPeriod);
    uint32_t expiry() const;
    void setExpiry(uint32_t newExpiry);

private:
    uint16_t m_period;
    uint32_t m_expiry;
};

}
#endif // TEMPORARYLOCATIONTRACKINGCONTROL_H
