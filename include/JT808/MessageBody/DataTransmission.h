#ifndef DATATRANSMISSION_H
#define DATATRANSMISSION_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class DataTransmission : public MessageBodyBase
{
public:
    DataTransmission();
    DataTransmission(uint8_t type, const ByteArray& data);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const DataTransmission& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint8_t type() const;
    void setType(uint8_t newType);
    ByteArray data() const;
    void setData(const ByteArray& newData);

private:
    uint8_t m_type = 0;
    ByteArray m_data;
};

}
#endif // DATATRANSMISSION_H
