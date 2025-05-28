#include "JT808/MessageBody/EventReport.h"

namespace JT808::MessageBody {

EventReport::EventReport(uint8_t id)
    : MessageBodyBase()
    , m_id(id)
{
}

void EventReport::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void EventReport::parse(const uint8_t* data, int size)
{
    m_id = data[0];

    setIsValid(true);
}

std::vector<uint8_t> EventReport::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_id);

    return result;
}

bool EventReport::operator==(const EventReport& other) const
{
    return m_id == other.m_id;
}

uint8_t EventReport::id() const
{
    return m_id;
}

void EventReport::setId(uint8_t newId)
{
    m_id = newId;
}

}
