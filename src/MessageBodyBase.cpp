#include "JT808/MessageBody/MessageBodyBase.h"
#include "nlohmann/json-schema.hpp"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

bool MessageBodyBase::isValid() const
{
    return m_isValid;
}

void MessageBodyBase::setIsValid(bool newIsValid)
{
    m_isValid = newIsValid;
}

MessageBodyBase::MessageBodyBase(const nlohmann::json& schema)
{
    m_validator.set_root_schema(schema);
}

bool MessageBodyBase::validate(const nlohmann::json& data)
{
    nlohmann::json_schema::basic_error_handler err;
    m_validator.validate(data, err);
    return !err;
}

void MessageBodyBase::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void MessageBodyBase::parse(const uint8_t* /*data*/, int /*size*/)
{
    m_isValid = true;
}

std::vector<uint8_t> MessageBodyBase::package()
{
    return {};
}

void MessageBodyBase::fromJson(const nlohmann::json& data)
{
    m_isValid = validate(data);
}

nlohmann::json MessageBodyBase::toJson()
{
    return {};
}
}
