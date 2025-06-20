#include "JT808/MessageBody/TerminalParameterQueryResponse.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/TerminalParameter.h"
#include "JT808/Schema/TerminalParameterQueryResponseSchema.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

TerminalParameterQueryResponse::TerminalParameterQueryResponse()
    : MessageBodyBase(Schema::TerminalParameterQueryResponseSchema)
{
}

TerminalParameterQueryResponse::TerminalParameterQueryResponse(const uint8_t* data, int size)
    : MessageBodyBase(Schema::TerminalParameterQueryResponseSchema)
{
    parse(data, size);
}

TerminalParameterQueryResponse::TerminalParameterQueryResponse(const Json& data)
    : MessageBodyBase(Schema::TerminalParameterQueryResponseSchema)
{
    fromJson(data);
}

TerminalParameterQueryResponse::TerminalParameterQueryResponse(uint16_t seq, const TerminalParameters& params)
    : MessageBodyBase(Schema::TerminalParameterQueryResponseSchema)
    , m_seq(seq)
    , m_params(params)
{
}

void TerminalParameterQueryResponse::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void TerminalParameterQueryResponse::parse(const uint8_t* data, int size)
{
    int pos = 0;
    int pos1 = 0;

    // seq
    m_seq = Utils::endianSwap16(data);
    pos += sizeof(m_seq);
    // length
    uint8_t const length = data[pos++];
    // params
    for (int i = 0; i < length; i++) {
        TerminalParameter param;
        pos1 = param.parse(data + pos, size);
        m_params.push_back(param);
        pos += pos1;
    }

    setIsValid(true);
}

ByteArray TerminalParameterQueryResponse::package()
{
    ByteArray result;
    // seq
    Utils::appendU16(m_seq, result);
    // length
    result.push_back(m_params.size());
    // params
    for (auto& item : m_params) {
        Utils::append(item.package(), result);
    }

    return result;
}

bool TerminalParameterQueryResponse::operator==(const TerminalParameterQueryResponse& other) const
{
    return m_seq == other.m_seq && m_params == other.m_params;
}

void TerminalParameterQueryResponse::fromJson(const Json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        if (data["length"] > 0) {
            for (auto& item : data["params"]) {
                TerminalParameter param(item);
                m_params.push_back(param);
            }
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json TerminalParameterQueryResponse::toJson()
{
    Json result({{"seq", m_seq}, {"length", m_params.size()}, {"params", {}}});

    for (auto& item : m_params) {
        result["params"].push_back(item.toJson());
    }
    result["seq"] = m_seq;

    return result;
}

uint16_t TerminalParameterQueryResponse::seq() const
{
    return m_seq;
}

void TerminalParameterQueryResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

TerminalParameters TerminalParameterQueryResponse::params() const
{
    return m_params;
}

void TerminalParameterQueryResponse::setParams(const TerminalParameters& newParams)
{
    m_params = newParams;
}

}
