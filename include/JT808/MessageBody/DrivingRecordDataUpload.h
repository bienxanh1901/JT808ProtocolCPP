#ifndef DRIVINGRECORDDATAUPLOAD_H
#define DRIVINGRECORDDATAUPLOAD_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class DrivingRecordDataUpload : public MessageBodyBase
{
public:
    DrivingRecordDataUpload();
    DrivingRecordDataUpload(uint16_t seq, uint8_t command, const ByteArray& param);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const DrivingRecordDataUpload& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);
    uint8_t command() const;
    void setCommand(uint8_t newCommand);
    ByteArray data() const;
    void setData(const ByteArray& newData);

private:
    uint16_t m_seq = 0;
    uint8_t m_command = 0;
    ByteArray m_data;
};

}

#endif // DRIVINGRECORDDATAUPLOAD_H
