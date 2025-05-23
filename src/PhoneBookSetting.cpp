#include "JT808/MessageBody/PhoneBookSetting.h"

namespace JT808::MessageBody {

PhoneBookSetting::PhoneBookSetting(AreaSettingType type, const std::vector<ContactItem>& contacts)
    : MessageBodyBase()
    , m_type(type)
    , m_length(contacts.size())
    , m_contacts(contacts)
{
}

void PhoneBookSetting::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void PhoneBookSetting::parse(const uint8_t* data, int size)
{
    int pos = 0;
    ContactItem item = {0};
    m_type = AreaSettingType(data[pos++]);
    m_length = data[pos++];

    for (int i = 0; i < m_length; i++) {
        item.type = data[pos++];
        item.phoneLength = data[pos++];
        item.phone.assign(data + pos, data + pos + item.phoneLength);
        pos += item.phoneLength;
        item.nameLength = data[pos++];
        item.name = Utils::gbkDecode(data + pos, item.nameLength);
        pos += item.nameLength;

        m_contacts.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> PhoneBookSetting::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);
    result.push_back(m_length);

    for (auto& item : m_contacts) {
        result.push_back(item.type);
        result.push_back(item.phoneLength);
        result.insert(result.end(), item.phone.begin(), item.phone.end());
        result.push_back(item.nameLength);
        Utils::appendGBK(item.name, result);
    }

    return result;
}

bool PhoneBookSetting::operator==(const PhoneBookSetting& other)
{
    bool result = m_type == other.m_type && m_length == other.m_length;
    if (result && m_length > 0) {
        for (int i = 0; i < m_length; i++) {
            if (!(m_contacts[i] == other.m_contacts[i])) {
                return false;
            }
        }
    }

    return true;
}

PhoneBookSetting::AreaSettingType PhoneBookSetting::type() const
{
    return m_type;
}

void PhoneBookSetting::setType(AreaSettingType newType)
{
    m_type = newType;
}

uint8_t PhoneBookSetting::length() const
{
    return m_length;
}

void PhoneBookSetting::setLength(uint8_t newLength)
{
    m_length = newLength;
}

std::vector<PhoneBookSetting::ContactItem> PhoneBookSetting::contacts() const
{
    return m_contacts;
}

void PhoneBookSetting::setContacts(const std::vector<ContactItem>& newContacts)
{
    m_contacts = newContacts;
}

}
