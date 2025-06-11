#include "JT808/MessageBody/SingleStoredMultimediaItemRetrievalUploadCommand.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/SingleStoredMultimediaItemRetrievalUploadCommandSchema.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

SingleStoredMultimediaItemRetrievalUploadCommand::SingleStoredMultimediaItemRetrievalUploadCommand()
    : MessageBodyBase(Schema::SingleStoredMultimediaItemRetrievalUploadCommandSchema)
{
}

SingleStoredMultimediaItemRetrievalUploadCommand::SingleStoredMultimediaItemRetrievalUploadCommand(uint32_t id,
                                                                                                   uint8_t isDelete)
    : MessageBodyBase(Schema::SingleStoredMultimediaItemRetrievalUploadCommandSchema)
    , m_id(id)
    , m_isDelete(isDelete)
{
}

void SingleStoredMultimediaItemRetrievalUploadCommand::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void SingleStoredMultimediaItemRetrievalUploadCommand::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;

    // id
    m_id = Utils::endianSwap32(data);
    pos += sizeof(m_id);
    // delete
    m_isDelete = data[pos];

    setIsValid(true);
}

ByteArray SingleStoredMultimediaItemRetrievalUploadCommand::package()
{
    ByteArray result;

    // id
    Utils::appendU32(m_id, result);
    // delete
    result.push_back(m_isDelete);

    return result;
}

bool SingleStoredMultimediaItemRetrievalUploadCommand::operator==(
    const SingleStoredMultimediaItemRetrievalUploadCommand& other) const
{
    return m_id == other.m_id && m_isDelete == other.m_isDelete;
}

void SingleStoredMultimediaItemRetrievalUploadCommand::fromJson(const Json& data)
{
    if (validate(data)) {
        m_id = data["id"];
        m_isDelete = data["delete"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json SingleStoredMultimediaItemRetrievalUploadCommand::toJson()
{
    return {{"id", m_id}, {"delete", m_isDelete}};
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
