#ifndef EVENTREPORT_H
#define EVENTREPORT_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class EventReport : public MessageBodyBase
{
public:
    EventReport();
    EventReport(uint8_t id);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const EventReport& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    uint8_t id() const;
    void setId(uint8_t newId);

private:
    uint8_t m_id = 0;
};

}

#endif // EVENTREPORT_H
