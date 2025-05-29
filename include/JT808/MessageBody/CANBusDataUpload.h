#ifndef CANBUSDATAUPLOAD_H
#define CANBUSDATAUPLOAD_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

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
        std::vector<uint8_t> package();

        void fromJson(const nlohmann::json& data);
        nlohmann::json toJson();
    };

    CANBusDataUpload();
    CANBusDataUpload(std::string time, const std::vector<ItemData>& data);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const CANBusDataUpload& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

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
