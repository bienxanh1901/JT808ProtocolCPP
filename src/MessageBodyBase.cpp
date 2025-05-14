#include "JT808/MessageBody/MessageBodyBase.h"

namespace JT808 {

namespace MessageBody {
bool MessageBodyBase::isValid() const
{
    return m_isValid;
}

std::vector<uint8_t> MessageBodyBase::rawData() const
{
    return m_rawData;
}

void MessageBodyBase::setRawData(const std::vector<uint8_t>& newRawData)
{
    m_rawData = newRawData;
}

MessageBodyBase::MessageBodyBase(const std::vector<uint8_t>& data)
    : m_rawData(data)
{
}

MessageBodyBase::MessageBodyBase(uint8_t* data, int size)
    : m_rawData(data, data + size)
{
}

void MessageBodyBase::parse()
{
    m_isValid = true;
}

void MessageBodyBase::package()
{
    m_isValid = true;
}
}
}
