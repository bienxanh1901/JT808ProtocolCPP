#include "JT808/MessageBody/InformationServiceCancel.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/InformationServiceCancelSchema.h"
#include <cstdint>

namespace JT808::MessageBody {

InformationServiceCancel::InformationServiceCancel()
    : MessageBodyBase(Schema::InformationServiceCancelSchema)
{
}

InformationServiceCancel::InformationServiceCancel(uint8_t id, uint8_t flag)
    : MessageBodyBase(Schema::InformationServiceCancelSchema)
    , m_id(id)
    , m_flag(flag)
{
}

void InformationServiceCancel::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void InformationServiceCancel::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;

    m_id = data[pos++];
    m_flag = data[pos];

    setIsValid(true);
}

ByteArray InformationServiceCancel::package()
{
    ByteArray result;

    result.push_back(m_id);
    result.push_back(m_flag);

    return result;
}

bool InformationServiceCancel::operator==(const InformationServiceCancel& other) const
{
    return m_flag == other.m_flag && m_id == other.m_id;
}

void InformationServiceCancel::fromJson(const Json& data)
{
    if (validate(data)) {
        m_id = data["id"];
        m_flag = data["flag"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json InformationServiceCancel::toJson()
{
    return {{"id", m_id}, {"flag", m_flag}};
}

uint8_t InformationServiceCancel::id() const
{
    return m_id;
}

void InformationServiceCancel::setId(uint8_t newId)
{
    m_id = newId;
}

uint8_t InformationServiceCancel::flag() const
{
    return m_flag;
}

void InformationServiceCancel::setFlag(uint8_t newFlag)
{
    m_flag = newFlag;
}

}
