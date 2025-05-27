#include "JT808/MessageBody/StorageMultimediaDataUploadCommand.h"

namespace JT808::MessageBody {

StorageMultimediaDataUploadCommand::StorageMultimediaDataUploadCommand(MediaType type, uint8_t channel, EventCode event,
                                                                       const std::string& startTime,
                                                                       const std::string& endTime, uint8_t isDelete)
    : StorageMultimediaDataRetrieval(type, channel, event, startTime, endTime)
    , m_isDelete(isDelete)
{
}

void StorageMultimediaDataUploadCommand::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void StorageMultimediaDataUploadCommand::parse(const uint8_t* data, int size)
{
    StorageMultimediaDataRetrieval::parse(data, size);
    m_isDelete = data[15];

    setIsValid(true);
}

std::vector<uint8_t> StorageMultimediaDataUploadCommand::package()
{
    std::vector<uint8_t> result(StorageMultimediaDataRetrieval::package());

    result.push_back(m_isDelete);

    return result;
}

bool StorageMultimediaDataUploadCommand::operator==(const StorageMultimediaDataUploadCommand& other)
{
    return StorageMultimediaDataRetrieval::operator==(other) && m_isDelete == other.m_isDelete;
}

uint8_t StorageMultimediaDataUploadCommand::isDelete() const
{
    return m_isDelete;
}

void StorageMultimediaDataUploadCommand::setIsDelete(uint8_t newIsDelete)
{
    m_isDelete = newIsDelete;
}

}
