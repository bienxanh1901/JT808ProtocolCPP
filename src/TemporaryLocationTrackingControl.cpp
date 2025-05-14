#include "JT808/MessageBody/TemporaryLocationTrackingControl.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {

TemporaryLocationTrackingControl::TemporaryLocationTrackingControl(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

TemporaryLocationTrackingControl::TemporaryLocationTrackingControl(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void TemporaryLocationTrackingControl::parse()
{
    uint8_t* data = m_rawData.data();
    int pos = 0;

    m_period = Utils::endianSwap16(data + pos);
    pos += sizeof(m_period);
    m_expiry = Utils::endianSwap32(data + pos);
    m_isValid = true;
}

void TemporaryLocationTrackingControl::package()
{
    Utils::U16Array u16Data = {0};
    Utils::U32Array u32Data = {0};

    m_rawData.clear();

    u16Data.value = Utils::endianSwap16(m_period);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    u32Data.value = Utils::endianSwap32(m_expiry);
    m_rawData.insert(m_rawData.end(), u32Data.array, u32Data.array + sizeof(u32Data));

    m_isValid = true;
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
