#ifndef ELECTRONICWAYBILLREPORT_H
#define ELECTRONICWAYBILLREPORT_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

/**
 * @brief The DrivingRecordDataCollectionCommand class
 */
class ElectronicWaybillReport : public MessageBodyBase
{
public:
    ElectronicWaybillReport();
    ElectronicWaybillReport(const std::vector<uint8_t>& data);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const ElectronicWaybillReport& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    std::vector<uint8_t> data() const;
    void setData(const std::vector<uint8_t>& newData);

private:
    std::vector<uint8_t> m_data;
};

}

#endif // ELECTRONICWAYBILLREPORT_H
