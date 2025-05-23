#include "JT808/MessageBody/CallbackPhone.h"

namespace JT808::MessageBody {

CallbackPhone::CallbackPhone(PhoneType type, const std::string& phone)
    : MessageBodyBase()
    , m_type(type)
    , m_phone(phone)
{
}

void CallbackPhone::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void CallbackPhone::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_type = PhoneType(data[pos++]);

    m_phone.assign(data + pos, data + size);

    setIsValid(true);
}

std::vector<uint8_t> CallbackPhone::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);
    result.insert(result.end(), m_phone.begin(), m_phone.end());

    return result;
}

bool CallbackPhone::operator==(const CallbackPhone& other)
{
    return m_type == other.m_type && m_phone == other.m_phone;
}

CallbackPhone::PhoneType CallbackPhone::type() const
{
    return m_type;
}

void CallbackPhone::settype(PhoneType newtype)
{
    m_type = newtype;
}

std::string CallbackPhone::phone() const
{
    return m_phone;
}

void CallbackPhone::setPhone(const std::string& newPhone)
{
    m_phone = newPhone;
}

}
