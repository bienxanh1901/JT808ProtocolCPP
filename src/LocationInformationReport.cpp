#include "JT808/MessageBody/LocationInformationReport.h"
#include "JT808/MessageBody/LocationInformation.h"
#include <cstdint>
#include <string>
#include <vector>

namespace JT808::MessageBody {

LocationInformationReport::LocationInformationReport(const AlarmFlags& alarm, const StatusFlags& status, uint32_t lat,
                                                     uint32_t lng, uint16_t alt, uint16_t speed, uint16_t bearing,
                                                     const std::string& time, const ExtraInfo& extra)
    : m_info(alarm, status, lat, lng, alt, speed, bearing, time, extra)
{
}

void LocationInformationReport::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void LocationInformationReport::parse(const uint8_t* data, int size)
{

    m_info.parse(data, size);

    setIsValid(true);
}

std::vector<uint8_t> LocationInformationReport::package()
{
    return m_info.package();
}

bool LocationInformationReport::operator==(const LocationInformationReport& other) const
{
    return m_info == other.m_info;
}

}
