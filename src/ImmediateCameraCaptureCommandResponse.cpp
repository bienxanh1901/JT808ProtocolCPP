#include "JT808/MessageBody/ImmediateCameraCaptureCommandResponse.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/ImmediateCameraCaptureCommandResponseSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

ImmediateCameraCaptureCommandResponse::ImmediateCameraCaptureCommandResponse()
    : MessageBodyBase(Schema::ImmediateCameraCaptureCommandResponseSchema)
{
}

ImmediateCameraCaptureCommandResponse::ImmediateCameraCaptureCommandResponse(uint16_t seq, ResponseResults result,
                                                                             const std::vector<uint32_t>& ids)
    : MessageBodyBase(Schema::ImmediateCameraCaptureCommandResponseSchema)
    , m_seq(seq)
    , m_result(result)
    , m_ids(ids)
{
}

void ImmediateCameraCaptureCommandResponse::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void ImmediateCameraCaptureCommandResponse::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    uint16_t length = 0;

    // seq
    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
    // result
    m_result = ResponseResults(data[pos++]);
    if (m_result == Succeeded) {
        // length
        length = Utils::endianSwap16(data + pos);
        pos += sizeof(length);
        // ids
        for (int i = 0; i < length; i++) {
            m_ids.push_back(Utils::endianSwap32(data + pos));
            pos += sizeof(uint32_t);
        }
    }

    setIsValid(true);
}

ByteArray ImmediateCameraCaptureCommandResponse::package()
{
    ByteArray result;
    // seq
    Utils::appendU16(m_seq, result);
    // result
    result.push_back(m_result);
    if (m_result == Succeeded) {
        // length
        Utils::appendU16(m_ids.size(), result);
        // ids
        for (auto& id : m_ids) {
            Utils::appendU32(id, result);
        }
    }
    return result;
}

bool ImmediateCameraCaptureCommandResponse::operator==(const ImmediateCameraCaptureCommandResponse& other) const
{
    return m_seq == other.m_seq && m_result == other.m_result && m_ids == other.m_ids;
}

void ImmediateCameraCaptureCommandResponse::fromJson(const Json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        m_result = ResponseResults(data["result"]);
        if (data["length"] > 0) {
            m_ids = data["ids"].get<std::vector<uint32_t>>();
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json ImmediateCameraCaptureCommandResponse::toJson()
{
    return {{"seq", m_seq}, {"result", m_result}, {"length", m_ids.size()}, {"ids", m_ids}};
}

ImmediateCameraCaptureCommandResponse::ResponseResults ImmediateCameraCaptureCommandResponse::result() const
{
    return m_result;
}

void ImmediateCameraCaptureCommandResponse::setResult(ResponseResults newResult)
{
    m_result = newResult;
}

std::vector<uint32_t> ImmediateCameraCaptureCommandResponse::ids() const
{
    return m_ids;
}

void ImmediateCameraCaptureCommandResponse::setIds(const std::vector<uint32_t>& newIds)
{
    m_ids = newIds;
}

uint16_t ImmediateCameraCaptureCommandResponse::seq() const
{
    return m_seq;
}

void ImmediateCameraCaptureCommandResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

}
