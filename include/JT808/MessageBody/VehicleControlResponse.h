#ifndef VEHICLECONTROLRESPONSE_H
#define VEHICLECONTROLRESPONSE_H

#include "LocationInformationReport.h"

namespace JT808::MessageBody {

class VehicleControlResponse : public LocationInformationReport
{
public:
    VehicleControlResponse() = default;
    VehicleControlResponse(uint16_t seq, const AlarmFlags& alarm, const StatusFlags& status, uint32_t latitude,
                           uint32_t longitude, uint16_t altitude, uint16_t speed, uint16_t bearing,
                           const std::string& time, const ExtraInfo& extra = {});
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const VehicleControlResponse& other);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
};

}
#endif // VEHICLECONTROLRESPONSE_H
