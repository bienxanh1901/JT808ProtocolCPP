#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Common.h"
#include "nlohmann/json-schema.hpp"
#include <cstdint>

namespace JT808::MessageBody {

bool MessageBodyBase::isValid() const
{
    return m_isValid;
}

void MessageBodyBase::setIsValid(bool newIsValid)
{
    m_isValid = newIsValid;
}

MessageBodyBase::MessageBodyBase(const Json& schema)
{
    m_validator.set_root_schema(schema);
}

bool MessageBodyBase::validate(const Json& data)
{
    nlohmann::json_schema::basic_error_handler err;
    m_validator.validate(data, err);
    return !err;
}

void MessageBodyBase::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void MessageBodyBase::parse(const uint8_t* data, int size)
{
    m_data.assign(data, data + size);
    m_isValid = true;
}

ByteArray MessageBodyBase::package()
{
    return m_data;
}

void MessageBodyBase::fromJson(const Json& data)
{
    m_data = data["data"].get<ByteArray>();
    m_isValid = true;
}

Json MessageBodyBase::toJson()
{

    return Json::object({{"data", m_data}});
}
}
