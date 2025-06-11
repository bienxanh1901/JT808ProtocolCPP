#ifndef RSAPUBLICKEY_H
#define RSAPUBLICKEY_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class RSAPublicKey : public MessageBodyBase
{
public:
    RSAPublicKey();
    RSAPublicKey(const ByteArray& data);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const RSAPublicKey& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    ByteArray data() const;
    void setData(const ByteArray& newData);

private:
    ByteArray m_data;
};

}
#endif // RSAPUBLICKEY_H
