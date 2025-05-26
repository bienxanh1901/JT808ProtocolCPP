#include "JT808/MessageBody/CANBusDataUpload.h"
#include "JT808/BCD.h"

namespace JT808::MessageBody {

CANBusDataUpload::CANBusDataUpload(const std::string& time, const std::vector<ItemData>& data)
    : MessageBodyBase()
    , m_time(time)
    , m_data(data)
{
}

void CANBusDataUpload::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void CANBusDataUpload::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // length
    uint16_t length = Utils::endianSwap16(data);
    pos += sizeof(length);
    // time
    m_time = BCD::toString(data + pos, 5);
    pos += 5;
    // data
    for (int i = 0; i < length; i++) {
        ItemData item = {0};
        item.parse(data + pos, 12);
        pos += 12;
        m_data.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> CANBusDataUpload::package()
{
    std::vector<uint8_t> result;

    Utils::appendU16(m_data.size(), result);
    Utils::appendBCD(m_time, result);

    for (auto& item : m_data) {
        std::vector<uint8_t> itemData(item.package());
        result.insert(result.end(), itemData.begin(), itemData.end());
    }

    return result;
}

bool CANBusDataUpload::operator==(const CANBusDataUpload& other)
{
    return m_time == other.m_time && m_data == other.m_data;
}

std::string CANBusDataUpload::time() const
{
    return m_time;
}

void CANBusDataUpload::setTime(const std::string& newTime)
{
    m_time = newTime;
}

std::vector<CANBusDataUpload::ItemData> CANBusDataUpload::data() const
{
    return m_data;
}

void CANBusDataUpload::setData(const std::vector<ItemData>& newData)
{
    m_data = newData;
}

}
