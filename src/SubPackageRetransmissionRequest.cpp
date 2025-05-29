#include "JT808/MessageBody/SubPackageRetransmissionRequest.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/SubPackageRetransmissionRequestSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

SubPackageRetransmissionRequest::SubPackageRetransmissionRequest()
    : MessageBodyBase(Schema::SubPackageRetransmissionRequestSchema)
{
}

SubPackageRetransmissionRequest::SubPackageRetransmissionRequest(uint16_t seq, const std::vector<uint16_t>& ids)
    : MessageBodyBase(Schema::SubPackageRetransmissionRequestSchema)
    , m_seq(seq)
    , m_ids(ids)
{
}

void SubPackageRetransmissionRequest::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void SubPackageRetransmissionRequest::parse(const uint8_t* data, int size)
{
    int pos = 0;
    uint8_t length = 0;

    // seq
    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
    // length
    length = data[pos++];

    if (length * 2 != size - pos) {
        setIsValid(false);
        return;
    }

    // ids
    for (uint8_t i = 0; i < length; ++i) {
        uint16_t const id = Utils::endianSwap16(data + pos);
        m_ids.push_back(id);
        pos += sizeof(id);
    }

    setIsValid(true);
}

std::vector<uint8_t> SubPackageRetransmissionRequest::package()
{
    std::vector<uint8_t> result;
    // seq
    Utils::appendU16(m_seq, result);
    // length
    result.push_back(m_ids.size());
    // ids
    Utils::append(m_ids, result);

    return result;
}

bool SubPackageRetransmissionRequest::operator==(const SubPackageRetransmissionRequest& other) const
{
    return m_seq == other.m_seq && m_ids == other.m_ids;
}

void SubPackageRetransmissionRequest::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        uint8_t const length = data["length"];
        if (length > 0) {
            m_ids = data["ids"].get<std::vector<uint16_t>>();
        }

        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json SubPackageRetransmissionRequest::toJson()
{
    return nlohmann::json::object({{"seq", m_seq}, {"length", m_ids.size()}, {"ids", m_ids}});
}

std::vector<uint16_t> SubPackageRetransmissionRequest::ids() const
{
    return m_ids;
}

void SubPackageRetransmissionRequest::setIds(const std::vector<uint16_t>& newIds)
{
    m_ids = newIds;
}

uint16_t SubPackageRetransmissionRequest::seq() const
{
    return m_seq;
}

void SubPackageRetransmissionRequest::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

}
