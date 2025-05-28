#include "JT808/MessageBody/StoredMultimediaDataRetrievalResponse.h"
#include "JT808/MessageBody/Multimedia.h"
#include "JT808/MessageBody/SequenceMessageBodyBase.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

StoredMultimediaDataRetrievalResponse::StoredMultimediaDataRetrievalResponse(
    uint16_t seq, const std::vector<MultimediaRetrievalData>& result)
    : SequenceMessageBodyBase(seq)
    , m_result(result)
{
}

void StoredMultimediaDataRetrievalResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void StoredMultimediaDataRetrievalResponse::parse(const uint8_t* data, int size)
{
    int pos = 2;
    uint16_t length = 0;
    // seq
    SequenceMessageBodyBase::parse(data, size);
    // length
    length = Utils::endianSwap16(data + pos);
    pos += sizeof(length);
    // item
    for (int i = 0; i < length; i++) {
        MultimediaRetrievalData item = {0};
        item.parse(data + pos, size);
        pos += 35;

        m_result.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> StoredMultimediaDataRetrievalResponse::package()
{
    std::vector<uint8_t> result(SequenceMessageBodyBase::package());

    // length
    Utils::appendU16(m_result.size(), result);
    // item
    for (auto& item : m_result) {
        Utils::append(item.package(), result);
    }

    return result;
}

bool StoredMultimediaDataRetrievalResponse::operator==(const StoredMultimediaDataRetrievalResponse& other) const
{
    return SequenceMessageBodyBase::operator==(other) && m_result == other.m_result;
}

std::vector<MultimediaRetrievalData> StoredMultimediaDataRetrievalResponse::result() const
{
    return m_result;
}

void StoredMultimediaDataRetrievalResponse::setResult(const std::vector<MultimediaRetrievalData>& newResult)
{
    m_result = newResult;
}

}
