#ifndef ELECTRONICWAYBILLREPORT_H
#define ELECTRONICWAYBILLREPORT_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

/**
 * @brief The DrivingRecordDataCollectionCommand class
 */
class ElectronicWaybillReport : public MessageBodyBase
{
public:
    ElectronicWaybillReport() = default;
    ElectronicWaybillReport(const std::string& data);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const ElectronicWaybillReport& other);

    uint32_t length() const;
    void setLength(uint32_t newLength);

    std::string data() const;
    void setData(const std::string& newData);

private:
    uint32_t m_length;
    std::string m_data;
};

}

#endif // ELECTRONICWAYBILLREPORT_H
