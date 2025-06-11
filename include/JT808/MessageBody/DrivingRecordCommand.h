#ifndef DRIVINGRECORDCOMMAND_H
#define DRIVINGRECORDCOMMAND_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

/**
 * @brief The DrivingRecordDataCollectionCommand class
 */
class DrivingRecordCommand : public MessageBodyBase
{
public:
    DrivingRecordCommand();
    DrivingRecordCommand(uint8_t command, const ByteArray& param);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const DrivingRecordCommand& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint8_t command() const;
    void setCommand(uint8_t newCommand);
    ByteArray param() const;
    void setParam(const ByteArray& newParam);

private:
    uint8_t m_command = 0;
    ByteArray m_param;
};

}

#endif // DRIVINGRECORDCOMMAND_H
