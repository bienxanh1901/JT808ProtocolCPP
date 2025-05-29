#ifndef DRIVINGRECORDDATAUPLOAD_H
#define DRIVINGRECORDDATAUPLOAD_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class DrivingRecordDataUpload : public MessageBodyBase
{
public:
    DrivingRecordDataUpload();
    DrivingRecordDataUpload(uint16_t seq, uint8_t command, const std::vector<uint8_t>& param);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const DrivingRecordDataUpload& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);
    uint8_t command() const;
    void setCommand(uint8_t newCommand);
    std::vector<uint8_t> data() const;
    void setData(const std::vector<uint8_t>& newData);

private:
    uint16_t m_seq = 0;
    uint8_t m_command = 0;
    std::vector<uint8_t> m_data;
};

}

#endif // DRIVINGRECORDDATAUPLOAD_H
