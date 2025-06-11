#include "JT808/MessageBody/EventReport.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/EventReportSchema.h"
#include <cstdint>

namespace JT808::MessageBody {

EventReport::EventReport()
    : MessageBodyBase(Schema::EventReportSchema)
{
}

EventReport::EventReport(uint8_t id)
    : MessageBodyBase(Schema::EventReportSchema)
    , m_id(id)
{
}

void EventReport::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void EventReport::parse(const uint8_t* data, int /*size*/)
{
    m_id = data[0];

    setIsValid(true);
}

ByteArray EventReport::package()
{
    ByteArray result;

    result.push_back(m_id);

    return result;
}

bool EventReport::operator==(const EventReport& other) const
{
    return m_id == other.m_id;
}

void EventReport::fromJson(const Json& data)
{
    if (validate(data)) {
        m_id = data["id"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json EventReport::toJson()
{
    return {{"id", m_id}};
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
