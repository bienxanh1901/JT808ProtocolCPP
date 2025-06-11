#include "JT808/MessageBody/StoredMultimediaDataUploadCommand.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/Multimedia.h"
#include "JT808/MessageBody/StoredMultimediaDataRetrieval.h"
#include "JT808/Schema/StoredMultimediaDataUploadCommandSchema.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

StoredMultimediaDataUploadCommand::StoredMultimediaDataUploadCommand()
    : StoredMultimediaDataRetrieval(Schema::StoredMultimediaDataUploadCommandSchema)
{
}

StoredMultimediaDataUploadCommand::StoredMultimediaDataUploadCommand(MediaType type, uint8_t channel, EventCode event,
                                                                     const std::string& startTime,
                                                                     const std::string& endTime, uint8_t isDelete)
    : StoredMultimediaDataRetrieval(Schema::StoredMultimediaDataUploadCommandSchema, type, channel, event, startTime,
                                    endTime)
    , m_isDelete(isDelete)
{
}

void StoredMultimediaDataUploadCommand::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void StoredMultimediaDataUploadCommand::parse(const uint8_t* data, int size)
{
    // data
    StoredMultimediaDataRetrieval::parse(data, size);
    // delete
    m_isDelete = data[15];

    setIsValid(true);
}

ByteArray StoredMultimediaDataUploadCommand::package()
{
    // data
    ByteArray result(StoredMultimediaDataRetrieval::package());
    // delete
    result.push_back(m_isDelete);

    return result;
}

bool StoredMultimediaDataUploadCommand::operator==(const StoredMultimediaDataUploadCommand& other) const
{
    return StoredMultimediaDataRetrieval::operator==(other) && m_isDelete == other.m_isDelete;
}

void StoredMultimediaDataUploadCommand::fromJson(const Json& data)
{
    if (validate(data)) {
        StoredMultimediaDataRetrieval::fromJson(data);
        m_isDelete = data["delete"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json StoredMultimediaDataUploadCommand::toJson()
{
    Json result(StoredMultimediaDataRetrieval::toJson());

    result["delete"] = m_isDelete;

    return result;
}

uint8_t StoredMultimediaDataUploadCommand::isDelete() const
{
    return m_isDelete;
}

void StoredMultimediaDataUploadCommand::setIsDelete(uint8_t newIsDelete)
{
    m_isDelete = newIsDelete;
}

}
