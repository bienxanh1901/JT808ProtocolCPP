#include "JT808/MessageBody/QuestionResponse.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/QuestionResponseSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

QuestionResponse::QuestionResponse()
    : MessageBodyBase(Schema::QuestionResponseSchema)
{
}

QuestionResponse::QuestionResponse(uint16_t seq, uint8_t id)
    : MessageBodyBase(Schema::QuestionResponseSchema)
    , m_seq(seq)
    , m_id(id)
{
}

void QuestionResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void QuestionResponse::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;

    // seq
    m_seq = Utils::endianSwap16(data);
    pos += sizeof(m_seq);
    // id
    m_id = data[pos];

    setIsValid(true);
}

std::vector<uint8_t> QuestionResponse::package()
{
    std::vector<uint8_t> result;
    // seq
    Utils::appendU16(m_seq, result);
    // id
    result.push_back(m_id);

    return result;
}

bool QuestionResponse::operator==(const QuestionResponse& other) const
{
    return m_seq == other.m_seq && m_id == other.m_id;
}

void QuestionResponse::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        m_id = data["id"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json QuestionResponse::toJson()
{
    return {{"seq", m_seq}, {"id", m_id}};
}

uint8_t QuestionResponse::id() const
{
    return m_id;
}

void QuestionResponse::setId(uint8_t newId)
{
    m_id = newId;
}

uint16_t QuestionResponse::seq() const
{
    return m_seq;
}

void QuestionResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

}
