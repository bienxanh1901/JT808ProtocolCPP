#include "JT808/MessageBody/PhoneBookSetting.h"

namespace JT808::MessageBody {

PhoneBookSetting::PhoneBookSetting(SettingType type, const std::vector<ContactItem>& contacts)
    : MessageBodyBase()
    , m_type(type)
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
    int pos1 = 0;
    uint8_t length = 0;

    // type
    m_type = SettingType(data[pos++]);
    // length
    length = data[pos++];
    // contacts
    for (int i = 0; i < length; i++) {
        ContactItem item = {0};
        pos1 = item.parse(data + pos, size);
        pos += pos1;
        m_contacts.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> PhoneBookSetting::package()
{
    std::vector<uint8_t> result;
    // type
    result.push_back(m_type);
    // length
    result.push_back(m_contacts.size());
    // contacts
    for (auto& item : m_contacts) {
        Utils::append(item.package(), result);
    }

    return result;
}

bool PhoneBookSetting::operator==(const PhoneBookSetting& other) const
{
    return m_type == other.m_type && m_contacts == other.m_contacts;
}

PhoneBookSetting::SettingType PhoneBookSetting::type() const
{
    return m_type;
}

void PhoneBookSetting::setType(SettingType newType)
{
    m_type = newType;
}

std::vector<PhoneBookSetting::ContactItem> PhoneBookSetting::contacts() const
{
    return m_contacts;
}

void PhoneBookSetting::setContacts(const std::vector<ContactItem>& newContacts)
{
    m_contacts = newContacts;
}

bool PhoneBookSetting::ContactItem::operator==(const ContactItem& other) const
{
    return type == other.type && phone == other.phone && name == other.name;
}

int PhoneBookSetting::ContactItem::parse(const uint8_t* data, int size)
{
    int pos = 0;
    uint16_t length = 0;

    // type
    type = data[pos++];
    // phone length
    length = data[pos++];
    // phone number
    phone.assign(data + pos, data + pos + length);
    pos += length;
    // name length
    length = data[pos++];
    // name
    name = Utils::gbkDecode(data + pos, length);
    pos += length;

    return pos;
}

std::vector<uint8_t> PhoneBookSetting::ContactItem::package()
{
    std::vector<uint8_t> result;
    // type
    result.push_back(type);
    // phone length
    result.push_back(phone.size());
    // phone
    Utils::append(phone, result);
    // name length
    result.push_back(name.size());
    // name
    Utils::appendGBK(name, result);

    return result;
}

}
