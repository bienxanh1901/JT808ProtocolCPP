#include "JT808/MessageBody/MessageBodyBase.h"
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
}
