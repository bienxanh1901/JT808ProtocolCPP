#ifndef LOCATIONINFORMATIONREPORT_H
#define LOCATIONINFORMATIONREPORT_H

#include "LocationInformation.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class LocationInformationReport : public MessageBodyBase
{
public:
    LocationInformationReport();
    LocationInformationReport(const nlohmann::json& schema);
    LocationInformationReport(const AlarmFlags& alarm, const StatusFlags& status, uint32_t lat, uint32_t lng,
                              uint16_t alt, uint16_t speed, uint16_t bearing, const std::string& time,
                              const ExtraInfo& extra = {});
    LocationInformationReport(const nlohmann::json& schema, const AlarmFlags& alarm, const StatusFlags& status,
                              uint32_t lat, uint32_t lng, uint16_t alt, uint16_t speed, uint16_t bearing,
                              const std::string& time, const ExtraInfo& extra = {});
    LocationInformationReport(const nlohmann::json& schema, LocationInformation info);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const LocationInformationReport& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    LocationInformation info() const;
    void setInfo(const LocationInformation& newInfo);

private:
    LocationInformation m_info;
};

}
#endif // LOCATIONINFORMATIONREPORT_H
