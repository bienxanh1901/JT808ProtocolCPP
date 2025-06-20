#include "JT808/MessageBody/StoredMultimediaDataUploadCommand.h"
#include "JT808/BCD.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/Multimedia.h"
#include "JT808/Schema/StoredMultimediaDataUploadCommandSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

StoredMultimediaDataUploadCommand::StoredMultimediaDataUploadCommand()
    : MessageBodyBase(Schema::StoredMultimediaDataUploadCommandSchema)
{
}

StoredMultimediaDataUploadCommand::StoredMultimediaDataUploadCommand(const uint8_t* data, int size)
    : MessageBodyBase(Schema::StoredMultimediaDataUploadCommandSchema)
{
    parse(data, size);
}

StoredMultimediaDataUploadCommand::StoredMultimediaDataUploadCommand(const Json& data)
    : MessageBodyBase(Schema::StoredMultimediaDataUploadCommandSchema)
{
    fromJson(data);
}

StoredMultimediaDataUploadCommand::StoredMultimediaDataUploadCommand(MediaType type, uint8_t channel, EventCode event,
                                                                     const std::string& startTime,
                                                                     const std::string& endTime, uint8_t isDelete)
    : MessageBodyBase(Schema::StoredMultimediaDataUploadCommandSchema)
    , m_type(type)
    , m_channel(channel)
    , m_event(event)
    , m_startTime(std::move(startTime))
    , m_endTime(std::move(endTime))
    , m_isDelete(isDelete)
{
}

void StoredMultimediaDataUploadCommand::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void StoredMultimediaDataUploadCommand::parse(const uint8_t* data, int size)
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
    pos += 6;
    // delete
    m_isDelete = data[pos];

    setIsValid(true);
}

ByteArray StoredMultimediaDataUploadCommand::package()
{
    ByteArray result;
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
    // delete
    result.push_back(m_isDelete);

    return result;
}

bool StoredMultimediaDataUploadCommand::operator==(const StoredMultimediaDataUploadCommand& other) const
{
    return m_type == other.m_type && m_event == other.m_event && m_channel == other.m_channel
        && m_startTime == other.m_startTime && m_endTime == other.m_endTime && m_isDelete == other.m_isDelete;
}

void StoredMultimediaDataUploadCommand::fromJson(const Json& data)
{
    if (validate(data)) {
        m_type = MediaType(data["type"]);
        m_channel = data["channel"];
        m_event = EventCode(data["event"]);
        m_startTime = data["start_time"];
        m_endTime = data["end_time"];
        m_isDelete = data["delete"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json StoredMultimediaDataUploadCommand::toJson()
{

    return Json::object({{"type", m_type},
                         {"channel", m_channel},
                         {"event", m_event},
                         {"start_time", m_startTime},
                         {"end_time", m_endTime},
                         {"delete", m_isDelete}});
}

uint8_t StoredMultimediaDataUploadCommand::isDelete() const
{
    return m_isDelete;
}

void StoredMultimediaDataUploadCommand::setIsDelete(uint8_t newIsDelete)
{
    m_isDelete = newIsDelete;
}

MediaType StoredMultimediaDataUploadCommand::type() const
{
    return m_type;
}

void StoredMultimediaDataUploadCommand::setType(MediaType newType)
{
    m_type = newType;
}

uint8_t StoredMultimediaDataUploadCommand::channel() const
{
    return m_channel;
}

void StoredMultimediaDataUploadCommand::setChannel(uint8_t newChannel)
{
    m_channel = newChannel;
}

EventCode StoredMultimediaDataUploadCommand::event() const
{
    return m_event;
}

void StoredMultimediaDataUploadCommand::setEvent(EventCode newEvent)
{
    m_event = newEvent;
}

std::string StoredMultimediaDataUploadCommand::startTime() const
{
    return m_startTime;
}

void StoredMultimediaDataUploadCommand::setStartTime(const std::string& newStartTime)
{
    m_startTime = newStartTime;
}

std::string StoredMultimediaDataUploadCommand::endTime() const
{
    return m_endTime;
}

void StoredMultimediaDataUploadCommand::setEndTime(const std::string& newEndTime)
{
    m_endTime = newEndTime;
}

}
