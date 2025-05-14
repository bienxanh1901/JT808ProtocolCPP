#include "JT808/MessageBody/SubPackageRetransmissionRequest.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

SubPackageRetransmissionRequest::SubPackageRetransmissionRequest(uint16_t seq, const std::vector<uint16_t>& ids)
    : SequenceMessageBodyBase(seq)
    , m_length(ids.size())
    , m_ids(ids)
{
}

void SubPackageRetransmissionRequest::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void SubPackageRetransmissionRequest::parse(const uint8_t* data, int size)
{
    int pos = 2;

    SequenceMessageBodyBase::parse(data, size);

    m_length = data[pos++];

    if (m_length * 2 != size - pos) {
        setIsValid(false);
        return;
    }

    uint16_t id = 0;
    for (uint8_t i = 0; i < m_length; ++i) {
        id = Utils::endianSwap16(data + pos);
        m_ids.push_back(id);
        pos += sizeof(id);
    }

    setIsValid(true);
}

std::vector<uint8_t> SubPackageRetransmissionRequest::package()
{
    std::vector<uint8_t> result(SequenceMessageBodyBase::package());
    result.push_back(m_length);

    for (const auto& id : m_ids) {
        Utils::appendU16(id, result);
    }

    return result;
}

bool SubPackageRetransmissionRequest::operator==(const SubPackageRetransmissionRequest& other)
{
    return SequenceMessageBodyBase::operator==(other) && m_length == other.m_length && m_ids == other.m_ids;
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
