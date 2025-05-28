#include <cstdint>
#include <string>
#include <utility>

#include "JT808/MessageBody/CallbackPhone.h"
#include "JT808/Utils.h"
#include <vector>

namespace JT808::MessageBody {

CallbackPhone::CallbackPhone(PhoneType type, std::string phone)
    : m_type(type)
    , m_phone(std::move(phone))
{
}

void CallbackPhone::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void CallbackPhone::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // type
    m_type = PhoneType(data[pos++]);
    // phone
    m_phone.assign(data + pos, data + size);

    setIsValid(true);
}

std::vector<uint8_t> CallbackPhone::package()
{
    std::vector<uint8_t> result;
    // type
    result.push_back(m_type);
    // phone
    Utils::append(m_phone, result);

    return result;
}

bool CallbackPhone::operator==(const CallbackPhone& other) const
{
    return m_type == other.m_type && m_phone == other.m_phone;
}

std::string CallbackPhone::phone() const
{
    return m_phone;
}

void CallbackPhone::setPhone(const std::string& newPhone)
{
    m_phone = newPhone;
}

CallbackPhone::PhoneType CallbackPhone::type() const
{
    return m_type;
}

void CallbackPhone::setType(PhoneType newType)
{
    m_type = newType;
}

}
