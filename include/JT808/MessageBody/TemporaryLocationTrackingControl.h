#ifndef TEMPORARYLOCATIONTRACKINGCONTROL_H
#define TEMPORARYLOCATIONTRACKINGCONTROL_H

#include "MessageBodyBase.h"

#include <stdint.h>
#include <vector>

namespace JT808 {
namespace MessageBody {

class TemporaryLocationTrackingControl : public MessageBodyBase
{
public:
    TemporaryLocationTrackingControl(const std::vector<uint8_t>& data = {});
    TemporaryLocationTrackingControl(uint8_t* data, int size);

    void parse() override;
    void package() override;

    uint16_t period() const;
    void setPeriod(uint16_t newPeriod);
    uint32_t expiry() const;
    void setExpiry(uint32_t newExpiry);

private:
    uint16_t m_period;
    uint32_t m_expiry;
};

}
}
#endif // TEMPORARYLOCATIONTRACKINGCONTROL_H
