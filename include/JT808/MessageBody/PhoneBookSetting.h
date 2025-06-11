#ifndef PHONEBOOKSETTING_H
#define PHONEBOOKSETTING_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

namespace JT808::MessageBody {

class PhoneBookSetting : public MessageBodyBase
{
public:
    enum SettingType : uint8_t
    {
        DeleteAllContacts = 0,
        UpdatePhoneBook,
        AppendPhoneBook,
        ModifyPhoneBook
    };

    enum PhoneType : uint8_t
    {
        IncommingCallPhone = 1,
        OutgoingCallPhone = 2,
        InOutCallPhone = 3
    };

    struct ContactItem
    {
        uint8_t type = 0;
        std::string phone;
        std::string name;

        bool operator==(const ContactItem& other) const;
        int parse(const uint8_t* data, int size);
        ByteArray package() const;

        void fromJson(const Json& data);
        Json toJson();
    };

    PhoneBookSetting();
    PhoneBookSetting(SettingType type, const std::vector<ContactItem>& contacts);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const PhoneBookSetting& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    SettingType type() const;
    void setType(SettingType newType);
    std::vector<ContactItem> contacts() const;
    void setContacts(const std::vector<ContactItem>& newContacts);

private:
    SettingType m_type = DeleteAllContacts;
    std::vector<ContactItem> m_contacts;
};

}
#endif // PHONEBOOKSETTING_H
