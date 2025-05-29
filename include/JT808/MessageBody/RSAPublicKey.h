#ifndef RSAPUBLICKEY_H
#define RSAPUBLICKEY_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class RSAPublicKey : public MessageBodyBase
{
public:
    RSAPublicKey();
    RSAPublicKey(const std::vector<uint8_t>& data);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const RSAPublicKey& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    std::vector<uint8_t> data() const;
    void setData(const std::vector<uint8_t>& newData);

private:
    std::vector<uint8_t> m_data;
};

}
#endif // RSAPUBLICKEY_H
