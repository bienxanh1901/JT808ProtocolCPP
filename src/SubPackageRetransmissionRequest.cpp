#include "JT808/MessageBody/SubPackageRetransmissionRequest.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

SubPackageRetransmissionRequest::SubPackageRetransmissionRequest(uint16_t seq, const std::vector<uint16_t>& ids)
    : SequenceMessageBodyBase(seq)
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
    uint8_t length = 0;

    // seq
    SequenceMessageBodyBase::parse(data, size);
    // length
    length = data[pos++];

    if (length * 2 != size - pos) {
        setIsValid(false);
        return;
    }

    // ids
    for (uint8_t i = 0; i < length; ++i) {
        uint16_t id = Utils::endianSwap16(data + pos);
        m_ids.push_back(id);
        pos += sizeof(id);
    }

    setIsValid(true);
}

std::vector<uint8_t> SubPackageRetransmissionRequest::package()
{
    // seq
    std::vector<uint8_t> result(SequenceMessageBodyBase::package());
    // length
    result.push_back(m_ids.size());
    // ids
    Utils::append(m_ids, result);

    return result;
}

bool SubPackageRetransmissionRequest::operator==(const SubPackageRetransmissionRequest& other) const
{
    return SequenceMessageBodyBase::operator==(other) && m_ids == other.m_ids;
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
