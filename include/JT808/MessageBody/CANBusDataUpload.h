#ifndef CANBUSDATAUPLOAD_H
#define CANBUSDATAUPLOAD_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class CANBusDataUpload : public MessageBodyBase
{
public:
    union CANId {
        struct
        {
            uint32_t id : 29;
            uint32_t dataCollectionMethod : 1;
            uint32_t frameType : 1;
            uint32_t channel : 1;
        } bits;
        uint8_t bytes[4];
        uint32_t value = 0;
    };

    union CANData {
        uint8_t bytes[8];
        uint64_t value = 0;
    };

    struct ItemData
    {
        CANId id = {0};
        CANData data = {0};

        bool operator==(const ItemData& other) const;
        void parse(const uint8_t* rawData, int size);
        std::vector<uint8_t> package();
    };

    CANBusDataUpload() = default;
    CANBusDataUpload(const std::string& time, const std::vector<ItemData>& data);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const CANBusDataUpload& other) const;

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
