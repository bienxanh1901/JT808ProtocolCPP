#ifndef DRIVINGRECORDDATAUPLOAD_H
#define DRIVINGRECORDDATAUPLOAD_H

#include "DrivingRecordCommand.h"

namespace JT808::MessageBody {

class DrivingRecordDataUpload : public DrivingRecordCommand
{
public:
    DrivingRecordDataUpload() = default;
    DrivingRecordDataUpload(uint16_t seq, uint8_t command, const std::string& param);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const DrivingRecordDataUpload& other);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
};

}

#endif // DRIVINGRECORDDATAUPLOAD_H
