#ifndef LOCATIONINFORMATIONREPORT_H
#define LOCATIONINFORMATIONREPORT_H

#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "LocationInformation.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class LocationInformationReport : public MessageBodyBase
{
public:
    LocationInformationReport();
    LocationInformationReport(const BasicLocationInformation& basic, const ExtraLocationInformation& extra);
    LocationInformationReport(LocationInformation info);
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
