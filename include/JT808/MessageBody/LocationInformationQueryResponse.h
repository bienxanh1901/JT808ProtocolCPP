#ifndef LOCATIONINFORMATIONQUERYRESPONSE_H
#define LOCATIONINFORMATIONQUERYRESPONSE_H

#include "LocationInformation.h"
#include "MessageBodyBase.h"

#include <stdint.h>
#include <string>
#include <vector>

namespace JT808 {
namespace MessageBody {

class LocationInformationQueryResponse : public MessageBodyBase
{
public:
    LocationInformationQueryResponse(const std::vector<uint8_t>& data = {});
    LocationInformationQueryResponse(uint8_t* data, int size);

    void parse() override;
    void package() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);
    AlarmFlags alarm() const;
    void setAlarm(const AlarmFlags& newAlarm);
    StatusFlags status() const;
    void setStatus(const StatusFlags& newStatus);
    uint32_t latitude() const;
    void setLatitude(uint32_t newLatitude);
    uint32_t longitude() const;
    void setLongitude(uint32_t newLongitude);
    uint16_t altitude() const;
    void setAltitude(uint16_t newAltitude);
    uint16_t speed() const;
    void setSpeed(uint16_t newSpeed);
    uint16_t bearing() const;
    void setBearing(uint16_t newBearing);
    std::string time() const;
    void setTime(const std::string& newTime);
    ExtraInfo extra() const;
    void setExtra(const ExtraInfo& newExtra);

private:
    uint16_t m_seq;
    AlarmFlags m_alarm = {0};
    StatusFlags m_status = {0};
    uint32_t m_latitude = 0;
    uint32_t m_longitude = 0;
    uint16_t m_altitude = 0;
    uint16_t m_speed = 0;
    uint16_t m_bearing = 0;
    std::string m_time = "";
    ExtraInfo m_extra;
};

}
}
#endif // LOCATIONINFORMATIONQUERYRESPONSE_H
