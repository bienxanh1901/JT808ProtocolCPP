#include "JT808/MessageBody/VehicleControlResponse.h"

namespace JT808::MessageBody {

VehicleControlResponse::VehicleControlResponse(uint16_t seq, const AlarmFlags& alarm, const StatusFlags& status,
                                               uint32_t latitude, uint32_t longitude, uint16_t altitude, uint16_t speed,
                                               uint16_t bearing, const std::string& time, const ExtraInfo& extra)
    : m_seq(seq)
    , LocationInformationReport(alarm, status, latitude, longitude, altitude, speed, bearing, time, extra)
{
}

void VehicleControlResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void VehicleControlResponse::parse(const uint8_t* data, int size)
{
    m_seq = Utils::endianSwap16(data);
    LocationInformationReport::parse(data + 2, size - 2);
}

std::vector<uint8_t> VehicleControlResponse::package()
{
    std::vector<uint8_t> result;
    std::vector<uint8_t> tmp(LocationInformationReport::package());

    Utils::appendU16(m_seq, result);

    result.insert(result.end(), tmp.begin(), tmp.end());

    return result;
}

bool VehicleControlResponse::operator==(const VehicleControlResponse& other)
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
