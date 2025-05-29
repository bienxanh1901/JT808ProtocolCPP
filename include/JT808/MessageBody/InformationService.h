#ifndef INFORMATIONSERVICE_H
#define INFORMATIONSERVICE_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class InformationService : public MessageBodyBase
{
public:
    InformationService();
    InformationService(uint8_t type, std::string info);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const InformationService& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

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
