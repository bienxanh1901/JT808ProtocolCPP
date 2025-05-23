#include "JT808/MessageBody/EventSetting.h"

namespace JT808::MessageBody {

EventSetting::EventSetting(SettingTypes type, const std::vector<Event>& events)
    : MessageBodyBase()
    , m_type(type)
    , m_length(events.size())
    , m_events(events)
{
}

void EventSetting::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void EventSetting::parse(const uint8_t* data, int size)
{
    int pos = 0;
    Event event = {0};

    m_type = SettingTypes(data[pos++]);

    if (m_type > DeleteAllEvents) {
        m_length = data[pos++];

        for (int i = 0; i < m_length; i++) {
            event.id = data[pos++];
            event.length = data[pos++];
            if (event.length > 0) {
                event.content = Utils::gbkDecode(data + pos, event.length);
                pos += event.length;
            }
            m_events.push_back(event);
        }
    }

    setIsValid(true);
}

std::vector<uint8_t> EventSetting::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);

    if (m_type > DeleteAllEvents) {
        result.push_back(m_length);
        for (auto& event : m_events) {
            result.push_back(event.id);
            result.push_back(event.length);
            if (event.length) {
                Utils::appendGBK(event.content, result);
            }
        }
    }

    return result;
}

bool EventSetting::operator==(const EventSetting& other)
{
    bool result = m_type == other.m_type && m_length == other.m_length;
    if (result && m_length > 0) {
        for (int i = 0; i < m_length; i++) {
            if (!(m_events[i] == other.m_events[i])) {
                return false;
            }
        }
    }

    return true;
}

EventSetting::SettingTypes EventSetting::type() const
{
    return m_type;
}

void EventSetting::setType(SettingTypes newType)
{
    m_type = newType;
}

uint8_t EventSetting::length() const
{
    return m_length;
}

void EventSetting::setLength(uint8_t newLength)
{
    m_length = newLength;
}

std::vector<EventSetting::Event> EventSetting::events() const
{
    return m_events;
}

void EventSetting::setEvents(const std::vector<Event>& newEvents)
{
    m_events = newEvents;
}
}
