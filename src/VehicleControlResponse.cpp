#include "JT808/MessageBody/VehicleControlResponse.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "JT808/MessageBody/LocationInformation.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/VehicleControlResponseSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

VehicleControlResponse::VehicleControlResponse()
    : MessageBodyBase(Schema::VehicleControlResponseSchema)
{
}

VehicleControlResponse::VehicleControlResponse(uint8_t seq, const LocationInformation& location)
    : MessageBodyBase(Schema::VehicleControlResponseSchema)
    , m_seq(seq)
    , m_info(location)
{
}

VehicleControlResponse::VehicleControlResponse(uint16_t seq, const BasicLocationInformation& basic,
                                               const ExtraLocationInformation& extra)
    : MessageBodyBase(Schema::VehicleControlResponseSchema)
    , m_seq(seq)
    , m_info(basic, extra)
{
}

void VehicleControlResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void VehicleControlResponse::parse(const uint8_t* data, int size)
{
    // seq
    m_seq = Utils::endianSwap16(data);
    // location information
    m_info.parse(data + 2, size - 2);

    setIsValid(true);
}

std::vector<uint8_t> VehicleControlResponse::package()
{
    std::vector<uint8_t> result;
    // seq
    Utils::appendU16(m_seq, result);
    // location information
    Utils::append(m_info.package(), result);

    return result;
}

bool VehicleControlResponse::operator==(const VehicleControlResponse& other) const
{
    return m_seq == other.m_seq && m_info == other.m_info;
}

void VehicleControlResponse::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_seq = data["seq"];
        m_info.fromJson(data["location"]);
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json VehicleControlResponse::toJson()
{
    return nlohmann::json::object({{"seq", m_seq}, {"location", m_info.toJson()}});
}

uint16_t VehicleControlResponse::seq() const
{
    return m_seq;
}

void VehicleControlResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

LocationInformation VehicleControlResponse::info() const
{
    return m_info;
}

void VehicleControlResponse::setInfo(const LocationInformation& newInfo)
{
    m_info = newInfo;
}
}
