#include "JT808/MessageBody/TerminalParameterQueryResponse.h"
#include "JT808/MessageBody/TerminalParameter.h"
#include "JT808/MessageBody/TerminalParameterSetting.h"
#include "JT808/Schema/TerminalParameterQueryResponseSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

TerminalParameterQueryResponse::TerminalParameterQueryResponse()
    : TerminalParameterSetting(Schema::TerminalParameterQueryResponseSchema)
{
}

TerminalParameterQueryResponse::TerminalParameterQueryResponse(uint16_t seq, const TerminalParameters& params)
    : m_seq(seq)
    , TerminalParameterSetting(Schema::TerminalParameterQueryResponseSchema, params)
{
}

void TerminalParameterQueryResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalParameterQueryResponse::parse(const uint8_t* data, int /*size*/)
{
    // seq
    m_seq = Utils::endianSwap16(data);
    // params
    TerminalParameterSetting::parse(data + sizeof(m_seq), sizeof(m_seq));
}

std::vector<uint8_t> TerminalParameterQueryResponse::package()
{
    std::vector<uint8_t> result;
    // seq
    Utils::appendU16(m_seq, result);
    // params
    Utils::append(TerminalParameterSetting::package(), result);

    return result;
}

bool TerminalParameterQueryResponse::operator==(const TerminalParameterQueryResponse& other) const
{
    return m_seq == other.m_seq && TerminalParameterSetting::operator==(other);
}

void TerminalParameterQueryResponse::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        TerminalParameterSetting::fromJson(data);
    } else {
        setIsValid(false);
    }
}

nlohmann::json TerminalParameterQueryResponse::toJson()
{
    nlohmann::json result(TerminalParameterSetting::toJson());
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

}
