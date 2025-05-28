#ifndef DATACOMPRESSIONREPORT_H
#define DATACOMPRESSIONREPORT_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class DataCompressionReport : public MessageBodyBase
{
public:
    DataCompressionReport() = default;
    DataCompressionReport(const std::vector<uint8_t>& data);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const DataCompressionReport& other) const;

    std::vector<uint8_t> data() const;
    void setData(const std::vector<uint8_t>& newData);

private:
    std::vector<uint8_t> m_data;
};

}
#endif // DATACOMPRESSIONREPORT_H
