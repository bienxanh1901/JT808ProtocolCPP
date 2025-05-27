#ifndef CALLBACKPHONE_H
#define CALLBACKPHONE_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class CallbackPhone : public MessageBodyBase
{
public:
    enum PhoneType : uint8_t
    {
        OrdinaryPhone = 0,
        MonitoringPhone
    };

    CallbackPhone() = default;
    CallbackPhone(PhoneType type, const std::string& phone);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const CallbackPhone& other);

    std::string phone() const;
    void setPhone(const std::string& newPhone);

    PhoneType type() const;
    void setType(PhoneType newType);

private:
    PhoneType m_type = OrdinaryPhone;
    std::string m_phone;
};

}
#endif // CALLBACKPHONE_H
