#ifndef LOCATIONINFORMATIONQUERYRESPONSE_H
#define LOCATIONINFORMATIONQUERYRESPONSE_H

#include "JT808/Common.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "JT808/MessageBody/LocationInformation.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class LocationInformationQueryResponse : public MessageBodyBase
{
public:
    LocationInformationQueryResponse();
    LocationInformationQueryResponse(uint16_t seq, LocationInformation location);
    LocationInformationQueryResponse(uint16_t seq, const BasicLocationInformation& basic,
                                     const ExtraLocationInformation& extra);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const LocationInformationQueryResponse& other) const;

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
#endif // LOCATIONINFORMATIONQUERYRESPONSE_H
