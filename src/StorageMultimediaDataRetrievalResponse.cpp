#include "JT808/MessageBody/StorageMultimediaDataRetrievalResponse.h"

namespace JT808::MessageBody {

StorageMultimediaDataRetrievalResponse::StorageMultimediaDataRetrievalResponse(
    uint16_t seq, const std::vector<MultimediaRetrievalData>& result)
    : SequenceMessageBodyBase(seq)
    , m_result(result)
{
}

void StorageMultimediaDataRetrievalResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void StorageMultimediaDataRetrievalResponse::parse(const uint8_t* data, int size)
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

std::vector<uint8_t> StorageMultimediaDataRetrievalResponse::package()
{
    std::vector<uint8_t> result(SequenceMessageBodyBase::package());

    // length
    Utils::appendU16(m_result.size(), result);
    // item
    for (auto& item : m_result) {
        std::vector<uint8_t> itemData(item.package());
        result.insert(result.end(), itemData.begin(), itemData.end());
    }

    return result;
}

bool StorageMultimediaDataRetrievalResponse::operator==(const StorageMultimediaDataRetrievalResponse& other)
{
    return SequenceMessageBodyBase::operator==(other) && m_result == other.m_result;
}

std::vector<MultimediaRetrievalData> StorageMultimediaDataRetrievalResponse::result() const
{
    return m_result;
}

void StorageMultimediaDataRetrievalResponse::setResult(const std::vector<MultimediaRetrievalData>& newResult)
{
    m_result = newResult;
}

}
