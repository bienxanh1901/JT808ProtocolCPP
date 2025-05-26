#include "JT808/MessageBody/LocationInformationQueryResponse.h"

namespace JT808::MessageBody {

LocationInformationQueryResponse::LocationInformationQueryResponse(uint16_t seq, const AlarmFlags& alarm,
                                                                   const StatusFlags& status, uint32_t lat,
                                                                   uint32_t lng, uint16_t alt, uint16_t speed,
                                                                   uint16_t bearing, const std::string& time,
                                                                   const ExtraInfo& extra)
    : m_seq(seq)
    , LocationInformationReport(alarm, status, lat, lng, alt, speed, bearing, time, extra)
{
}

void LocationInformationQueryResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void LocationInformationQueryResponse::parse(const uint8_t* data, int size)
{
    m_seq = Utils::endianSwap16(data);
    LocationInformationReport::parse(data + 2, size - 2);
}

std::vector<uint8_t> LocationInformationQueryResponse::package()
{
    std::vector<uint8_t> result;
    std::vector<uint8_t> tmp(LocationInformationReport::package());

    Utils::appendU16(m_seq, result);

    result.insert(result.end(), tmp.begin(), tmp.end());

    return result;
}

bool LocationInformationQueryResponse::operator==(const LocationInformationQueryResponse& other)
{
    return m_seq == other.m_seq && LocationInformationReport::operator==(other);
}

uint16_t LocationInformationQueryResponse::seq() const
{
    return m_seq;
}

void LocationInformationQueryResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}
}
