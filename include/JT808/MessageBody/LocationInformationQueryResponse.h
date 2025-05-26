#ifndef LOCATIONINFORMATIONQUERYRESPONSE_H
#define LOCATIONINFORMATIONQUERYRESPONSE_H

#include "LocationInformationReport.h"

namespace JT808::MessageBody {

class LocationInformationQueryResponse : public LocationInformationReport
{
public:
    LocationInformationQueryResponse() = default;
    LocationInformationQueryResponse(uint16_t seq, const AlarmFlags& alarm, const StatusFlags& status, uint32_t lat,
                                     uint32_t lng, uint16_t alt, uint16_t speed, uint16_t bearing,
                                     const std::string& time, const ExtraInfo& extra = {});
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const LocationInformationQueryResponse& other);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
};

}
#endif // LOCATIONINFORMATIONQUERYRESPONSE_H
