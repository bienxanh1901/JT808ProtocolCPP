#include "JT808/MessageBody/ImmediateCameraCaptureCommandResponse.h"
#include "JT808/MessageBody/SequenceMessageBodyBase.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

ImmediateCameraCaptureCommandResponse::ImmediateCameraCaptureCommandResponse(uint16_t seq, ResponseResults result,
                                                                             const std::vector<uint32_t>& ids)
    : SequenceMessageBodyBase(seq)
    , m_result(result)
    , m_ids(ids)
{
}

void ImmediateCameraCaptureCommandResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void ImmediateCameraCaptureCommandResponse::parse(const uint8_t* data, int size)
{
    int pos = 2;
    uint16_t length = 0;

    // seq
    SequenceMessageBodyBase::parse(data, size);
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

std::vector<uint8_t> ImmediateCameraCaptureCommandResponse::package()
{
    std::vector<uint8_t> result(SequenceMessageBodyBase::package());

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
    return SequenceMessageBodyBase::operator==(other) && m_result == other.m_result && m_ids == other.m_ids;
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

}
