#ifndef INFORMATIONSERVICE_H
#define INFORMATIONSERVICE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

class InformationService : public MessageBodyBase
{
public:
    InformationService();
    InformationService(uint8_t type, std::string info);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const InformationService& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint8_t type() const;
    void setType(uint8_t newType);
    std::string info() const;
    void setInfo(const std::string& newInfo);

private:
    uint8_t m_type = 0;
    std::string m_info;
};

}
#endif // INFORMATIONSERVICE_H
