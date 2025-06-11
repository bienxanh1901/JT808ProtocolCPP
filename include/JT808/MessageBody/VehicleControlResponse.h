#ifndef VEHICLECONTROLRESPONSE_H
#define VEHICLECONTROLRESPONSE_H

#include "JT808/Common.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "LocationInformation.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class VehicleControlResponse : public MessageBodyBase
{
public:
    VehicleControlResponse();
    VehicleControlResponse(uint8_t seq, const LocationInformation& location);
    VehicleControlResponse(uint16_t seq, const BasicLocationInformation& basic, const ExtraLocationInformation& extra);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const VehicleControlResponse& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

    LocationInformation info() const;
    void setInfo(const LocationInformation& newInfo);

private:
    uint16_t m_seq = 0;
    LocationInformation m_info;
};

}
#endif // VEHICLECONTROLRESPONSE_H
