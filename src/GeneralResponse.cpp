#include "JT808/MessageBody/GeneralResponse.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/GeneralResponseSchema.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

GeneralResponse::GeneralResponse()
    : MessageBodyBase(Schema::GeneralResponseSchema)
{
}

GeneralResponse::GeneralResponse(uint16_t seq, uint16_t id, GeneralResponse::ResponseResults result)
    : MessageBodyBase(Schema::GeneralResponseSchema)
    , m_seq(seq)
    , m_id(id)
    , m_result(result)
{
}

void GeneralResponse::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void GeneralResponse::parse(const uint8_t* data, int size)
{
    if (size != 5) {
        setIsValid(false);
        return;
    }

    int pos = 0;
    // seq
    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
    // id
    m_id = Utils::endianSwap16(data + pos);
    pos += sizeof(m_id);
    // result
    m_result = ResponseResults(data[pos]);

    setIsValid(true);
}

ByteArray GeneralResponse::package()
{
    ByteArray result;
    // seq
    Utils::appendU16(m_seq, result);
    // id
    Utils::appendU16(m_id, result);
    // result
    result.push_back(m_result);

    setIsValid(true);
    return result;
}

bool GeneralResponse::operator==(const GeneralResponse& other) const
{
    return m_seq == other.m_seq && m_id == other.m_id && m_result == other.m_result;
}

void GeneralResponse::fromJson(const Json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        m_id = data["id"];
        m_result = ResponseResults(data["result"]);
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json GeneralResponse::toJson()
{
    return Json::object({{"seq", m_seq}, {"id", m_id}, {"result", m_result}});
}

uint16_t GeneralResponse::id() const
{
    return m_id;
}

void GeneralResponse::setId(uint16_t newId)
{
    m_id = newId;
}

GeneralResponse::ResponseResults GeneralResponse::result() const
{
    return m_result;
}

void GeneralResponse::setResult(ResponseResults newResult)
{
    m_result = newResult;
}

uint16_t GeneralResponse::seq() const
{
    return m_seq;
}

void GeneralResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

}
