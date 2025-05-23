#ifndef EVENTSETTING_H
#define EVENTSETTING_H
#include "MessageBodyBase.h"

#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class EventSetting : public MessageBodyBase
{
public:
    enum AreaSettingTypes
    {
        DeleteAllEvents = 0,
        UpgradeEvents,
        AppendEvents,
        ModifyEvents,
        DeleteSpecificEvents
    };

    struct Event
    {
        uint8_t id;
        uint8_t length;
        std::string content;

        bool operator==(const Event& other)
        {
            return id == other.id && length == other.length && content == other.content;
        }
    };

    EventSetting() = default;
    EventSetting(AreaSettingTypes type, const std::vector<Event>& events);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const EventSetting& other);

    AreaSettingTypes type() const;
    void setType(AreaSettingTypes newType);
    uint8_t length() const;
    void setLength(uint8_t newLength);
    std::vector<Event> events() const;
    void setEvents(const std::vector<Event>& newEvents);

private:
    AreaSettingTypes m_type = DeleteAllEvents;
    uint8_t m_length = 0;
    std::vector<Event> m_events;
};

}

#endif // EVENTSETTING_H
