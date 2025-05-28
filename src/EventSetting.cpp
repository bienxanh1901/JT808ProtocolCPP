#include "JT808/MessageBody/EventSetting.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

EventSetting::EventSetting(AreaSettingTypes type, const std::vector<Event>& events)
    : m_type(type)
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
    int pos1 = 0;
    // type
    m_type = AreaSettingTypes(data[pos++]);

    if (m_type > DeleteAllEvents) {
        // length
        uint8_t const length = data[pos++];
        // events
        for (int i = 0; i < length; i++) {
            Event item = {0};
            pos1 = item.parse(data + pos, size);
            pos += pos1;
            m_events.push_back(item);
        }
    }

    setIsValid(true);
}

std::vector<uint8_t> EventSetting::package()
{
    std::vector<uint8_t> result;
    // type
    result.push_back(m_type);
    if (m_type > DeleteAllEvents) {
        // length
        result.push_back(m_events.size());
        for (auto& item : m_events) {
            Utils::append(item.package(), result);
        }
    }

    return result;
}

bool EventSetting::operator==(const EventSetting& other) const
{
    return m_type == other.m_type && m_events == other.m_events;
}

EventSetting::AreaSettingTypes EventSetting::type() const
{
    return m_type;
}

void EventSetting::setType(AreaSettingTypes newType)
{
    m_type = newType;
}

std::vector<EventSetting::Event> EventSetting::events() const
{
    return m_events;
}

void EventSetting::setEvents(const std::vector<Event>& newEvents)
{
    m_events = newEvents;
}

bool EventSetting::Event::operator==(const Event& other) const
{
    return id == other.id && content == other.content;
}

int EventSetting::Event::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    uint8_t length = 0;
    // id
    id = data[pos++];
    // length
    length = data[pos++];
    // content
    if (length > 0) {
        content = Utils::gbkDecode(data + pos, length);
        pos += length;
    }

    return pos;
}

std::vector<uint8_t> EventSetting::Event::package() const
{
    std::vector<uint8_t> result;
    // id
    result.push_back(id);
    // length
    result.push_back(content.size());
    // content
    Utils::appendGBK(content, result);

    return result;
}

}
