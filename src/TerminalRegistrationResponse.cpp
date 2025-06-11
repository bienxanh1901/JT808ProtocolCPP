#include "JT808/MessageBody/TerminalRegistrationResponse.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/TerminalRegistrationResponseSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>

namespace JT808::MessageBody {

TerminalRegistrationResponse::TerminalRegistrationResponse()
    : MessageBodyBase(Schema::TerminalRegistrationResponseSchema)
{
}

TerminalRegistrationResponse::TerminalRegistrationResponse(uint16_t seq, ResponseResults result, std::string authCode)
    : MessageBodyBase(Schema::TerminalRegistrationResponseSchema)
    , m_seq(seq)
    , m_result(result)
    , m_authCode(std::move(authCode))
{
}

void TerminalRegistrationResponse::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void TerminalRegistrationResponse::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // seq
    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
    // result
    m_result = ResponseResults(data[pos++]);
    // authentication code
    if (m_result == Succeeded) {
        m_authCode.assign(data + pos, data + size);
    }

    setIsValid(true);
}

ByteArray TerminalRegistrationResponse::package()
{
    ByteArray result;
    // seq
    Utils::appendU16(m_seq, result);
    // result
    result.push_back(m_result);
    // authentication code
    if (m_result == Succeeded) {
        Utils::append(m_authCode, result);
    }

    return result;
}

bool TerminalRegistrationResponse::operator==(const TerminalRegistrationResponse& other) const
{
    return m_seq == other.m_seq && m_result == other.m_result && m_authCode == other.m_authCode;
}

void TerminalRegistrationResponse::fromJson(const Json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        m_result = ResponseResults(data["result"]);

        if (m_result == Succeeded) {
            m_authCode = data.value("auth_code", "");
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json TerminalRegistrationResponse::toJson()
{
    Json result(Json::object({{"seq", m_seq}, {"result", m_result}}));
    if (m_result == Succeeded) {
        result["auth_code"] = m_authCode;
    }
    return result;
}

TerminalRegistrationResponse::ResponseResults TerminalRegistrationResponse::result() const
{
    return m_result;
}

void TerminalRegistrationResponse::setResult(ResponseResults newResult)
{
    m_result = newResult;
}

std::string TerminalRegistrationResponse::authCode() const
{
    return m_authCode;
}

void TerminalRegistrationResponse::setAuthCode(const std::string& newAuthCode)
{
    m_authCode = newAuthCode;
}

uint16_t TerminalRegistrationResponse::seq() const
{
    return m_seq;
}

void TerminalRegistrationResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

}
