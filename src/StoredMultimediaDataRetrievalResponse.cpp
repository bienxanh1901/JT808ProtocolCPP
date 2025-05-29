#include "JT808/MessageBody/StoredMultimediaDataRetrievalResponse.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/Multimedia.h"
#include "JT808/Schema/StoredMultimediaDataRetrievalResponseSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

StoredMultimediaDataRetrievalResponse::StoredMultimediaDataRetrievalResponse()
    : MessageBodyBase(Schema::StoredMultimediaDataRetrievalResponseSchema)
{
}

StoredMultimediaDataRetrievalResponse::StoredMultimediaDataRetrievalResponse(
    uint16_t seq, const std::vector<MultimediaRetrievalData>& result)
    : MessageBodyBase(Schema::StoredMultimediaDataRetrievalResponseSchema)
    , m_seq(seq)
    , m_result(result)
{
}

void StoredMultimediaDataRetrievalResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void StoredMultimediaDataRetrievalResponse::parse(const uint8_t* data, int size)
{
    int pos = 0;
    uint16_t length = 0;
    // seq
    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
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
    std::vector<uint8_t> result;
    // seq
    Utils::appendU16(m_seq, result);
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
    return m_result == other.m_result;
}

void StoredMultimediaDataRetrievalResponse::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        if (data["length"] > 0) {
            for (auto& media : data["result"]) {
                MultimediaRetrievalData item = {0};
                item.fromJson(media);
                m_result.push_back(item);
            }
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json StoredMultimediaDataRetrievalResponse::toJson()
{
    nlohmann::json result(
        nlohmann::json::object({{"seq", m_seq}, {"length", m_result.size()}, {"result", nlohmann::json::array({})}}));
    for (auto& item : m_result) {
        result["result"].push_back(item.toJson());
    }
    return result;
}

std::vector<MultimediaRetrievalData> StoredMultimediaDataRetrievalResponse::result() const
{
    return m_result;
}

void StoredMultimediaDataRetrievalResponse::setResult(const std::vector<MultimediaRetrievalData>& newResult)
{
    m_result = newResult;
}

uint16_t StoredMultimediaDataRetrievalResponse::seq() const
{
    return m_seq;
}

void StoredMultimediaDataRetrievalResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

}
