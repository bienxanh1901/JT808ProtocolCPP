#include "JT808/MessageBody/StoredMultimediaDataRetrieval.h"
#include "JT808/BCD.h"

namespace JT808::MessageBody {

StoredMultimediaDataRetrieval::StoredMultimediaDataRetrieval(MediaType type, uint8_t channel, EventCode event,
                                                             const std::string& startTime, const std::string& endTime)
    : m_type(type)
    , m_channel(std::move(channel))
    , m_event(event)
    , m_startTime(startTime)
    , m_endTime(endTime)
{
}

void StoredMultimediaDataRetrieval::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void StoredMultimediaDataRetrieval::parse(const uint8_t* data, int size)
{
    int pos = 0;

    // type
    m_type = MediaType(data[pos++]);
    // channel
    m_channel = MediaType(data[pos++]);
    // event
    m_event = EventCode(data[pos++]);
    // startTime
    m_startTime = BCD::toString(data + pos, 6);
    pos += 6;
    // endTime
    m_endTime = BCD::toString(data + pos, 6);

    setIsValid(true);
}

std::vector<uint8_t> StoredMultimediaDataRetrieval::package()
{
    std::vector<uint8_t> result;
    // type
    result.push_back(m_type);
    // channel
    result.push_back(m_channel);
    // event
    result.push_back(m_event);
    // startTime
    Utils::appendBCD(m_startTime, result);
    // endTime
    Utils::appendBCD(m_endTime, result);

    return result;
}

bool StoredMultimediaDataRetrieval::operator==(const StoredMultimediaDataRetrieval& other) const
{
    return m_type == other.m_type && m_event == other.m_event && m_channel == other.m_channel
        && m_startTime == other.m_startTime && m_endTime == other.m_endTime;
}

MediaType StoredMultimediaDataRetrieval::type() const
{
    return m_type;
}

void StoredMultimediaDataRetrieval::setType(MediaType newType)
{
    m_type = newType;
}

uint8_t StoredMultimediaDataRetrieval::channel() const
{
    return m_channel;
}

void StoredMultimediaDataRetrieval::setChannel(uint8_t newChannel)
{
    m_channel = newChannel;
}

EventCode StoredMultimediaDataRetrieval::event() const
{
    return m_event;
}

void StoredMultimediaDataRetrieval::setEvent(EventCode newEvent)
{
    m_event = newEvent;
}

std::string StoredMultimediaDataRetrieval::startTime() const
{
    return m_startTime;
}

void StoredMultimediaDataRetrieval::setStartTime(const std::string& newStartTime)
{
    m_startTime = newStartTime;
}

std::string StoredMultimediaDataRetrieval::endTime() const
{
    return m_endTime;
}

void StoredMultimediaDataRetrieval::setEndTime(const std::string& newEndTime)
{
    m_endTime = newEndTime;
}

}
