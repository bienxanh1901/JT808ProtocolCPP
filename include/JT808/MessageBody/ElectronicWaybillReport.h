#ifndef ELECTRONICWAYBILLREPORT_H
#define ELECTRONICWAYBILLREPORT_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

/**
 * @brief The DrivingRecordDataCollectionCommand class
 */
class ElectronicWaybillReport : public MessageBodyBase
{
public:
    ElectronicWaybillReport();
    ElectronicWaybillReport(const uint8_t* data, int size);
    ElectronicWaybillReport(const Json& data);
    ElectronicWaybillReport(const ByteArray& data);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const ElectronicWaybillReport& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    ByteArray data() const;
    void setData(const ByteArray& newData);

private:
    ByteArray m_data;
};

}

#endif // ELECTRONICWAYBILLREPORT_H
