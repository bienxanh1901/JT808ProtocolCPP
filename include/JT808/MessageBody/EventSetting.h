#ifndef EVENTSETTING_H
#define EVENTSETTING_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

namespace JT808::MessageBody {

class EventSetting : public MessageBodyBase
{
public:
    enum AreaSettingTypes : uint8_t
    {
        DeleteAllEvents = 0,
        UpgradeEvents,
        AppendEvents,
        ModifyEvents,
        DeleteSpecificEvents
    };

    struct Event
    {
        uint8_t id = 0;
        std::string content;

        bool operator==(const Event& other) const;
        int parse(const uint8_t* data, int size);
        ByteArray package() const;
        void fromJson(const Json& data);
        Json toJson();
    };

    EventSetting();
    EventSetting(AreaSettingTypes type, const std::vector<Event>& events);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const EventSetting& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    AreaSettingTypes type() const;
    void setType(AreaSettingTypes newType);
    std::vector<Event> events() const;
    void setEvents(const std::vector<Event>& newEvents);

private:
    AreaSettingTypes m_type = DeleteAllEvents;
    std::vector<Event> m_events;
};

}

#endif // EVENTSETTING_H
