#include "JT808/MessageBody/VehicleControlResponse.h"

namespace JT808::MessageBody {

VehicleControlResponse::VehicleControlResponse(uint16_t seq, const AlarmFlags& alarm, const StatusFlags& status,
                                               uint32_t lat, uint32_t lng, uint16_t alt, uint16_t speed,
                                               uint16_t bearing, const std::string& time, const ExtraInfo& extra)
    : m_seq(seq)
    , LocationInformationReport(alarm, status, lat, lng, alt, speed, bearing, time, extra)
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
    LocationInformationReport::parse(data + 2, size - 2);
}

std::vector<uint8_t> VehicleControlResponse::package()
{
    std::vector<uint8_t> result;
    std::vector<uint8_t> tmp(LocationInformationReport::package());
    // seq
    Utils::appendU16(m_seq, result);
    // location information
    Utils::append(LocationInformationReport::package(), result);

    return result;
}

bool VehicleControlResponse::operator==(const VehicleControlResponse& other) const
{
    return m_seq == other.m_seq && LocationInformationReport::operator==(other);
}

uint16_t VehicleControlResponse::seq() const
{
    return m_seq;
}

void VehicleControlResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}
}
