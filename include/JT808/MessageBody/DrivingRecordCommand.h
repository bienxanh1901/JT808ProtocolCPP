#ifndef DRIVINGRECORDCOMMAND_H
#define DRIVINGRECORDCOMMAND_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

/**
 * @brief The DrivingRecordDataCollectionCommand class
 */
class DrivingRecordCommand : public MessageBodyBase
{
public:
    DrivingRecordCommand() = default;
    DrivingRecordCommand(uint8_t command, const std::string& param = "");
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const DrivingRecordCommand& other);

    uint8_t command() const;
    void setCommand(uint8_t newCommand);
    std::string param() const;
    void setParam(const std::string& newParam);

private:
    uint8_t m_command;
    std::string m_param;
};

}

#endif // DRIVINGRECORDCOMMAND_H
