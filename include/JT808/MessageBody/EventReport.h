#ifndef EVENTREPORT_H
#define EVENTREPORT_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class EventReport : public MessageBodyBase
{
public:
    EventReport();
    EventReport(uint8_t id);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const EventReport& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint8_t id() const;
    void setId(uint8_t newId);

private:
    uint8_t m_id = 0;
};

}

#endif // EVENTREPORT_H
