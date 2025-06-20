#include "JT808/MessageBody/PhoneBookSetting.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/PhoneBookSettingSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

PhoneBookSetting::PhoneBookSetting()
    : MessageBodyBase(Schema::PhoneBookSettingSchema)
{
}

PhoneBookSetting::PhoneBookSetting(const uint8_t* data, int size)
    : MessageBodyBase(Schema::PhoneBookSettingSchema)
{
    parse(data, size);
}

PhoneBookSetting::PhoneBookSetting(const Json& data)
    : MessageBodyBase(Schema::PhoneBookSettingSchema)
{
    fromJson(data);
}

PhoneBookSetting::PhoneBookSetting(SettingType type, const std::vector<ContactItem>& contacts)
    : MessageBodyBase(Schema::PhoneBookSettingSchema)
    , m_type(type)
    , m_contacts(contacts)
{
}

void PhoneBookSetting::parse(const ByteArray& data)
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
        ContactItem item;
        pos1 = item.parse(data + pos, size);
        pos += pos1;
        m_contacts.push_back(item);
    }

    setIsValid(true);
}

ByteArray PhoneBookSetting::package()
{
    ByteArray result;
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

void PhoneBookSetting::fromJson(const Json& data)
{
    if (validate(data)) {
        m_type = SettingType(data["type"]);
        if (data["length"] > 0) {
            for (auto& contact : data["contacts"]) {
                ContactItem item(contact);
                m_contacts.push_back(item);
            }
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json PhoneBookSetting::toJson()
{
    Json result({{"type", m_type}, {"length", m_contacts.size()}, {"contacts", {}}});
    for (auto& item : m_contacts) {
        result["contacts"].push_back(item.toJson());
    }

    return result;
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

PhoneBookSetting::ContactItem::ContactItem(const uint8_t* data, int size)
{
    parse(data, size);
}

PhoneBookSetting::ContactItem::ContactItem(const Json& data)
{
    fromJson(data);
}

PhoneBookSetting::ContactItem::ContactItem(uint8_t type, std::string phone, std::string name)
    : type(type)
    , phone(std::move(phone))
    , name(std::move(name))
{
}

bool PhoneBookSetting::ContactItem::operator==(const ContactItem& other) const
{
    return type == other.type && phone == other.phone && name == other.name;
}

int PhoneBookSetting::ContactItem::parse(const uint8_t* data, int /*size*/)
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

ByteArray PhoneBookSetting::ContactItem::package() const
{
    ByteArray result;
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

void PhoneBookSetting::ContactItem::fromJson(const Json& data)
{
    type = data["type"];
    phone = data["phone"];
    name = data["name"];
}

Json PhoneBookSetting::ContactItem::toJson()
{
    return {{"type", type}, {"phone", phone}, {"name", name}};
}

}
