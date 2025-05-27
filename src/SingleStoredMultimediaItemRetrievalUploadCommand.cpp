#include "JT808/MessageBody/SingleStoredMultimediaItemRetrievalUploadCommand.h"

namespace JT808::MessageBody {

SingleStoredMultimediaItemRetrievalUploadCommand::SingleStoredMultimediaItemRetrievalUploadCommand(uint32_t id,
                                                                                                   uint8_t isDelete)
    : MessageBodyBase()
    , m_id(id)
    , m_isDelete(isDelete)
{
}

void SingleStoredMultimediaItemRetrievalUploadCommand::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void SingleStoredMultimediaItemRetrievalUploadCommand::parse(const uint8_t* data, int size)
{
    int pos = 0;

    // id
    m_id = Utils::endianSwap32(data);
    pos += sizeof(m_id);
    // delete
    m_isDelete = data[pos];

    setIsValid(true);
}

std::vector<uint8_t> SingleStoredMultimediaItemRetrievalUploadCommand::package()
{
    std::vector<uint8_t> result;

    // id
    Utils::appendU32(m_id, result);
    // delete
    result.push_back(m_isDelete);

    return result;
}

bool SingleStoredMultimediaItemRetrievalUploadCommand::operator==(
    const SingleStoredMultimediaItemRetrievalUploadCommand& other)
{
    return m_id == other.m_id && m_isDelete == other.m_isDelete;
}

uint32_t SingleStoredMultimediaItemRetrievalUploadCommand::id() const
{
    return m_id;
}

void SingleStoredMultimediaItemRetrievalUploadCommand::setId(uint32_t newId)
{
    m_id = newId;
}

uint8_t SingleStoredMultimediaItemRetrievalUploadCommand::isDelete() const
{
    return m_isDelete;
}

void SingleStoredMultimediaItemRetrievalUploadCommand::setIsDelete(uint8_t newIsDelete)
{
    m_isDelete = newIsDelete;
}

}
