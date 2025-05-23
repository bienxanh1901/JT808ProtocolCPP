#ifndef INFORMATIONSERVICECANCEL_H
#define INFORMATIONSERVICECANCEL_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class InformationServiceCancel : public MessageBodyBase
{
public:
    InformationServiceCancel() = default;
    InformationServiceCancel(uint8_t id, uint8_t flag);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const InformationServiceCancel& other);

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
