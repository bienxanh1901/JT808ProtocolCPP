#ifndef INFORMATIONSERVICECANCEL_H
#define INFORMATIONSERVICECANCEL_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class InformationServiceCancel : public MessageBodyBase
{
public:
    InformationServiceCancel();
    InformationServiceCancel(uint8_t id, uint8_t flag);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const InformationServiceCancel& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint8_t id() const;
    void setId(uint8_t newId);
    uint8_t flag() const;
    void setFlag(uint8_t newFlag);

private:
    uint8_t m_id = 0;
    uint8_t m_flag = 0;
};

}
#endif // INFORMATIONSERVICECANCEL_H
