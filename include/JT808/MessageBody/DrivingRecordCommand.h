#ifndef DRIVINGRECORDCOMMAND_H
#define DRIVINGRECORDCOMMAND_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

/**
 * @brief The DrivingRecordDataCollectionCommand class
 */
class DrivingRecordCommand : public MessageBodyBase
{
public:
    DrivingRecordCommand();
    DrivingRecordCommand(uint8_t command, const std::vector<uint8_t>& param);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const DrivingRecordCommand& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    uint8_t command() const;
    void setCommand(uint8_t newCommand);
    std::vector<uint8_t> param() const;
    void setParam(const std::vector<uint8_t>& newParam);

private:
    uint8_t m_command = 0;
    std::vector<uint8_t> m_param;
};

}

#endif // DRIVINGRECORDCOMMAND_H
