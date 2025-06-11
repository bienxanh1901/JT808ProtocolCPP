#ifndef TEMPORARYLOCATIONTRACKINGCONTROL_H
#define TEMPORARYLOCATIONTRACKINGCONTROL_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class TemporaryLocationTrackingControl : public MessageBodyBase
{
public:
    TemporaryLocationTrackingControl();
    TemporaryLocationTrackingControl(uint16_t period, uint32_t expiry);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TemporaryLocationTrackingControl& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

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
