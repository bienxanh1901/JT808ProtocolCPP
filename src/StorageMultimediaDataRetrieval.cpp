#include "JT808/MessageBody/StorageMultimediaDataRetrieval.h"
#include "JT808/BCD.h"

namespace JT808::MessageBody {

StorageMultimediaDataRetrieval::StorageMultimediaDataRetrieval(MediaType type, uint8_t channel, EventCode event,
                                                               const std::string& startTime, const std::string& endTime)
    : m_type(type)
    , m_channel(std::move(channel))
    , m_event(event)
    , m_startTime(startTime)
    , m_endTime(endTime)
{
}

void StorageMultimediaDataRetrieval::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void StorageMultimediaDataRetrieval::parse(const uint8_t* data, int size)
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

std::vector<uint8_t> StorageMultimediaDataRetrieval::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);
    result.push_back(m_channel);
    result.push_back(m_event);
    Utils::appendBCD(m_startTime, result);
    Utils::appendBCD(m_endTime, result);

    return result;
}

bool StorageMultimediaDataRetrieval::operator==(const StorageMultimediaDataRetrieval& other)
{
    return m_type == other.m_type && m_event == other.m_event && m_channel == other.m_channel
        && m_startTime == other.m_startTime && m_endTime == other.m_endTime;
}

MediaType StorageMultimediaDataRetrieval::type() const
{
    return m_type;
}

void StorageMultimediaDataRetrieval::setType(MediaType newType)
{
    m_type = newType;
}

uint8_t StorageMultimediaDataRetrieval::channel() const
{
    return m_channel;
}

void StorageMultimediaDataRetrieval::setChannel(uint8_t newChannel)
{
    m_channel = newChannel;
}

EventCode StorageMultimediaDataRetrieval::event() const
{
    return m_event;
}

void StorageMultimediaDataRetrieval::setEvent(EventCode newEvent)
{
    m_event = newEvent;
}

std::string StorageMultimediaDataRetrieval::startTime() const
{
    return m_startTime;
}

void StorageMultimediaDataRetrieval::setStartTime(const std::string& newStartTime)
{
    m_startTime = newStartTime;
}

std::string StorageMultimediaDataRetrieval::endTime() const
{
    return m_endTime;
}

void StorageMultimediaDataRetrieval::setEndTime(const std::string& newEndTime)
{
    m_endTime = newEndTime;
}

}
