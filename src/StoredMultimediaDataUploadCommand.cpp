#include "JT808/MessageBody/StoredMultimediaDataUploadCommand.h"

namespace JT808::MessageBody {

StoredMultimediaDataUploadCommand::StoredMultimediaDataUploadCommand(MediaType type, uint8_t channel, EventCode event,
                                                                     const std::string& startTime,
                                                                     const std::string& endTime, uint8_t isDelete)
    : StoredMultimediaDataRetrieval(type, channel, event, startTime, endTime)
    , m_isDelete(isDelete)
{
}

void StoredMultimediaDataUploadCommand::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void StoredMultimediaDataUploadCommand::parse(const uint8_t* data, int size)
{
    StoredMultimediaDataRetrieval::parse(data, size);
    m_isDelete = data[15];

    setIsValid(true);
}

std::vector<uint8_t> StoredMultimediaDataUploadCommand::package()
{
    std::vector<uint8_t> result(StoredMultimediaDataRetrieval::package());

    result.push_back(m_isDelete);

    return result;
}

bool StoredMultimediaDataUploadCommand::operator==(const StoredMultimediaDataUploadCommand& other)
{
    return StoredMultimediaDataRetrieval::operator==(other) && m_isDelete == other.m_isDelete;
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
