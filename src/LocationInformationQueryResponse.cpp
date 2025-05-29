#include "JT808/MessageBody/LocationInformationQueryResponse.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "JT808/MessageBody/LocationInformation.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/LocationInformationQueryResponseSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

LocationInformationQueryResponse::LocationInformationQueryResponse()
    : MessageBodyBase(Schema::LocationInformationQueryResponseSchema)
{
}

LocationInformationQueryResponse::LocationInformationQueryResponse(uint16_t seq, LocationInformation location)
    : MessageBodyBase(Schema::LocationInformationQueryResponseSchema)
    , m_seq(seq)
    , m_info(std::move(location))
{
}

LocationInformationQueryResponse::LocationInformationQueryResponse(uint16_t seq, const BasicLocationInformation& basic,
                                                                   const ExtraLocationInformation& extra)
    : MessageBodyBase(Schema::LocationInformationQueryResponseSchema)
    , m_seq(seq)
    , m_info(basic, extra)
{
}

void LocationInformationQueryResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void LocationInformationQueryResponse::parse(const uint8_t* data, int size)
{
    m_seq = Utils::endianSwap16(data);
    m_info.parse(data + 2, size - 2);
    setIsValid(true);
}

std::vector<uint8_t> LocationInformationQueryResponse::package()
{
    std::vector<uint8_t> result;

    Utils::appendU16(m_seq, result);
    Utils::append(m_info.package(), result);

    return result;
}

bool LocationInformationQueryResponse::operator==(const LocationInformationQueryResponse& other) const
{
    return m_seq == other.m_seq && m_info == other.m_info;
}

void LocationInformationQueryResponse::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        m_info.fromJson(data["location"]);
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json LocationInformationQueryResponse::toJson()
{
    return nlohmann::json::object({{"seq", m_seq}, {"location", m_info.toJson()}});
}

uint16_t LocationInformationQueryResponse::seq() const
{
    return m_seq;
}

void LocationInformationQueryResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

LocationInformation LocationInformationQueryResponse::info() const
{
    return m_info;
}

void LocationInformationQueryResponse::setInfo(const LocationInformation& newInfo)
{
    m_info = newInfo;
}
}
