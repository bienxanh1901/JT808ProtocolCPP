#ifndef CANBUSDATAUPLOAD_H
#define CANBUSDATAUPLOAD_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

namespace JT808::MessageBody {

class CANBusDataUpload : public MessageBodyBase
{
public:
    union CANId {
        struct
        {
            uint32_t id : 29;
            uint32_t dataMethod : 1;
            uint32_t frameType : 1;
            uint32_t channel : 1;
        } bits;
        uint8_t bytes[4];
        uint32_t value = 0;
    };

    struct ItemData
    {
        CANId id = {0};
        std::string canData;

        bool operator==(const ItemData& other) const;
        void parse(const uint8_t* data, int size);
        ByteArray package();

        void fromJson(const Json& data);
        Json toJson();
    };

    CANBusDataUpload();
    CANBusDataUpload(std::string time, const std::vector<ItemData>& data);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const CANBusDataUpload& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    std::string time() const;
    void setTime(const std::string& newTime);
    std::vector<ItemData> data() const;
    void setData(const std::vector<ItemData>& newData);

private:
    std::string m_time;
    std::vector<ItemData> m_data;
};

}
#endif // CANBUSDATAUPLOAD_H
