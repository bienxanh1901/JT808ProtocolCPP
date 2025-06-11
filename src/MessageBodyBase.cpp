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

void MessageBodyBase::parse(const uint8_t* /*data*/, int /*size*/)
{
    m_isValid = true;
}

ByteArray MessageBodyBase::package()
{
    return {};
}

void MessageBodyBase::fromJson(const Json& data)
{
    m_isValid = validate(data);
}

Json MessageBodyBase::toJson()
{
    return {};
}
}
