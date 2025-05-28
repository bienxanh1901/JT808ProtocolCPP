#include "JT808/MessageBody/TemporaryLocationTrackingControl.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {

TemporaryLocationTrackingControl::TemporaryLocationTrackingControl(uint16_t period, uint32_t expiry)
    : MessageBodyBase()
    , m_period(period)
    , m_expiry(expiry)
{
}

void TemporaryLocationTrackingControl::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TemporaryLocationTrackingControl::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_period = Utils::endianSwap16(data + pos);
    pos += sizeof(m_period);
    m_expiry = Utils::endianSwap32(data + pos);

    setIsValid(true);
}

std::vector<uint8_t> TemporaryLocationTrackingControl::package()
{
    std::vector<uint8_t> result;

    Utils::appendU16(m_period, result);
    Utils::appendU32(m_expiry, result);

    return result;
}

bool TemporaryLocationTrackingControl::operator==(const TemporaryLocationTrackingControl& other) const
{
    return m_period == other.m_period && m_expiry == other.m_expiry;
}

uint16_t TemporaryLocationTrackingControl::period() const
{
    return m_period;
}

void TemporaryLocationTrackingControl::setPeriod(uint16_t newPeriod)
{
    m_period = newPeriod;
}

uint32_t TemporaryLocationTrackingControl::expiry() const
{
    return m_expiry;
}

void TemporaryLocationTrackingControl::setExpiry(uint32_t newExpiry)
{
    m_expiry = newExpiry;
}

}
}
