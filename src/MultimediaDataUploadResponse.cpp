#include "JT808/MessageBody/MultimediaDataUploadResponse.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/MultimediaDataUploadResponseSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

MultimediaDataUploadResponse::MultimediaDataUploadResponse()
    : MessageBodyBase(Schema::MultimediaDataUploadResponseSchema)
{
}

MultimediaDataUploadResponse::MultimediaDataUploadResponse(uint32_t id, std::vector<uint16_t>& retxIds)
    : MessageBodyBase(Schema::MultimediaDataUploadResponseSchema)
    , m_id(id)
    , m_retxIds(retxIds)
{
}

void MultimediaDataUploadResponse::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void MultimediaDataUploadResponse::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    uint8_t length = 0;
    // id
    m_id = Utils::endianSwap32(data + pos);
    pos += sizeof(m_id);
    // length
    length = data[pos++];
    // ids
    for (int i = 0; i < length; i++) {
        uint16_t const id = Utils::endianSwap16(data + pos);
        pos += sizeof(id);
        m_retxIds.push_back(id);
    }

    setIsValid(true);
}

ByteArray MultimediaDataUploadResponse::package()
{
    ByteArray result;

    // id
    Utils::appendU32(m_id, result);
    // length
    result.push_back(m_retxIds.size());
    // ids
    for (auto& id : m_retxIds) {
        Utils::appendU16(id, result);
    }

    return result;
}

bool MultimediaDataUploadResponse::operator==(const MultimediaDataUploadResponse& other) const
{
    return m_id == other.m_id && m_retxIds == other.m_retxIds;
}

void MultimediaDataUploadResponse::fromJson(const Json& data)
{
    if (validate(data)) {
        m_id = data["mm_id"];
        if (data["length"] > 0) {
            m_retxIds = data["retx_ids"].get<std::vector<uint16_t>>();
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json MultimediaDataUploadResponse::toJson()
{
    return {
        {"mm_id", m_id},
        {"length", m_retxIds.size()},
        {"retx_ids", m_retxIds},
    };
}

uint16_t MultimediaDataUploadResponse::id() const
{
    return m_id;
}

void MultimediaDataUploadResponse::setId(uint16_t newId)
{
    m_id = newId;
}

std::vector<uint16_t> MultimediaDataUploadResponse::retxIds() const
{
    return m_retxIds;
}

void MultimediaDataUploadResponse::setRetxIds(const std::vector<uint16_t>& newRetxIds)
{
    m_retxIds = newRetxIds;
}

}
