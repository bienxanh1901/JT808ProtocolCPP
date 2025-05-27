#ifndef DATATRANSMISSION_H
#define DATATRANSMISSION_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class DataTransmission : public MessageBodyBase
{
public:
    DataTransmission() = default;
    DataTransmission(uint8_t type, const std::vector<uint8_t>& data);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const DataTransmission& other);

    uint8_t type() const;
    void setType(uint8_t newType);
    std::vector<uint8_t> data() const;
    void setData(const std::vector<uint8_t>& newData);

private:
    uint8_t m_type = 0;
    std::vector<uint8_t> m_data;
};

}
#endif // DATATRANSMISSION_H
