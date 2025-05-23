#ifndef PHONEBOOKSETTING_H
#define PHONEBOOKSETTING_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class PhoneBookSetting : public MessageBodyBase
{
public:
    enum AreaSettingType
    {
        DeleteAllContacts = 0,
        UpdatePhoneBook,
        AppendPhoneBook,
        ModifyPhoneBook
    };

    enum PhoneType
    {
        IncommingCallPhone = 1,
        OutgoingCallPhone = 2,
        InOutCallPhone = 3
    };

    struct ContactItem
    {
        uint8_t type;
        uint8_t phoneLength;
        std::string phone;
        uint8_t nameLength;
        std::string name;

        bool operator==(const ContactItem& other)
        {
            return type == other.type && phoneLength == other.phoneLength && phone == other.phone
                && nameLength == other.nameLength && name == other.name;
        }
    };

    PhoneBookSetting() = default;
    PhoneBookSetting(AreaSettingType type, const std::vector<ContactItem>& contacts);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const PhoneBookSetting& other);

    AreaSettingType type() const;
    void setType(AreaSettingType newType);
    uint8_t length() const;
    void setLength(uint8_t newLength);
    std::vector<ContactItem> contacts() const;
    void setContacts(const std::vector<ContactItem>& newContacts);

private:
    AreaSettingType m_type = DeleteAllContacts;
    uint8_t m_length = 0;
    std::vector<ContactItem> m_contacts;
};

}
#endif // PHONEBOOKSETTING_H
