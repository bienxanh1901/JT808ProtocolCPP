#ifndef CALLBACKPHONE_H
#define CALLBACKPHONE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

class CallbackPhone : public MessageBodyBase
{
public:
    enum PhoneType : uint8_t
    {
        OrdinaryPhone = 0,
        MonitoringPhone
    };

    CallbackPhone();
    CallbackPhone(PhoneType type, std::string phone);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const CallbackPhone& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

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
