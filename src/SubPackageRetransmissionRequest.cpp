#include "JT808/MessageBody/SubPackageRetransmissionRequest.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {

SubPackageRetransmissionRequest::SubPackageRetransmissionRequest(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

SubPackageRetransmissionRequest::SubPackageRetransmissionRequest(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void SubPackageRetransmissionRequest::parse()
{
    uint8_t* data = m_rawData.data();
    int pos = 0;

    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
    m_length = data[pos++];

    if (m_length * 2 != m_rawData.size() - pos) {
        return;
    }

    uint16_t id = 0;
    for (uint8_t i = 0; i < m_length; ++i) {
        id = Utils::endianSwap16(data + pos);
        pos += sizeof(id);
        m_ids.push_back(id);
    }

    m_isValid = true;
}

void SubPackageRetransmissionRequest::package()
{
    Utils::U16Array u16Data = {0};

    m_rawData.clear();

    u16Data.value = Utils::endianSwap16(m_seq);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    m_rawData.push_back(m_length);

    for (const auto& id : m_ids) {
        u16Data.value = Utils::endianSwap16(id);
        m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));
    }

    m_isValid = true;
}

uint16_t SubPackageRetransmissionRequest::seq() const
{
    return m_seq;
}

void SubPackageRetransmissionRequest::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

uint8_t SubPackageRetransmissionRequest::length() const
{
    return m_length;
}

void SubPackageRetransmissionRequest::setLength(uint8_t newLength)
{
    m_length = newLength;
}

std::vector<uint16_t> SubPackageRetransmissionRequest::ids() const
{
    return m_ids;
}

void SubPackageRetransmissionRequest::setIds(const std::vector<uint16_t>& newIds)
{
    m_ids = newIds;
}

}
}
