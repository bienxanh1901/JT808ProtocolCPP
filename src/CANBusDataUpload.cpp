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
    // length
    Utils::appendU16(m_data.size(), result);
    // time
    Utils::appendBCD(m_time, result);
    // data
    for (auto& item : m_data) {
        Utils::append(item.package(), result);
    }

    return result;
}

bool CANBusDataUpload::operator==(const CANBusDataUpload& other) const
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

bool CANBusDataUpload::ItemData::operator==(const ItemData& other) const
{
    return id.value == other.id.value && data.value == other.data.value;
}

void CANBusDataUpload::ItemData::parse(const uint8_t* rawData, int size)
{
    int pos = 0;
    for (int i = 0; i < 4; i++) {
        id.bytes[i] = rawData[pos++];
    }

    for (int i = 0; i < 8; i++) {
        data.bytes[i] = rawData[pos++];
    }
}

std::vector<uint8_t> CANBusDataUpload::ItemData::package()
{
    std::vector<uint8_t> result;
    for (int i = 0; i < 4; i++) {
        result.push_back(id.bytes[i]);
    }

    for (int i = 0; i < 8; i++) {
        result.push_back(data.bytes[i]);
    }

    return result;
}

}
