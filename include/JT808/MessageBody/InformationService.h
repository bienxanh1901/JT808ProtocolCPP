#ifndef INFORMATIONSERVICE_H
#define INFORMATIONSERVICE_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class InformationService : public MessageBodyBase
{
public:
    InformationService() = default;
    InformationService(uint8_t type, const std::string& info);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const InformationService& other);

    uint8_t type() const;
    void setType(uint8_t newType);
    uint16_t length() const;
    void setLength(uint16_t newLength);
    std::string info() const;
    void setInfo(const std::string& newInfo);

private:
    uint8_t m_type = 0;
    uint16_t m_length = 0;
    std::string m_info;
};

}
#endif // INFORMATIONSERVICE_H
