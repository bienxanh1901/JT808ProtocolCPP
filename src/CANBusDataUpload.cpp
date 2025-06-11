#include "JT808/MessageBody/CANBusDataUpload.h"
#include "JT808/BCD.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/CANBusDataUploadSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

CANBusDataUpload::CANBusDataUpload()
    : MessageBodyBase(Schema::CANBusDataUploadSchema)
{
}

CANBusDataUpload::CANBusDataUpload(std::string time, const std::vector<ItemData>& data)
    : MessageBodyBase(Schema::CANBusDataUploadSchema)
    , m_time(std::move(time))
    , m_data(data)
{
}

void CANBusDataUpload::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void CANBusDataUpload::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    // length
    uint16_t const length = Utils::endianSwap16(data);
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

ByteArray CANBusDataUpload::package()
{
    ByteArray result;
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

void CANBusDataUpload::fromJson(const Json& data)
{
    if (validate(data)) {
        m_time = data["time"];

        if (data["length"] > 0) {
            for (auto& can : data["can_data"]) {
                ItemData item = {0};
                item.fromJson(can);
                m_data.push_back(item);
            }
        }

        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json CANBusDataUpload::toJson()
{
    Json result({{"length", m_data.size()}, {"time", m_time}, {"can_data", {}}});

    for (auto& item : m_data) {
        result["can_data"].push_back(item.toJson());
    }
    return result;
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
    return id.value == other.id.value && canData == other.canData;
}

void CANBusDataUpload::ItemData::parse(const uint8_t* data, int size)
{
    int pos = 0;
    for (unsigned char& byte : id.bytes) {
        byte = data[pos++];
    }

    canData.assign(data + pos, data + size);
}

ByteArray CANBusDataUpload::ItemData::package()
{
    ByteArray result;
    for (unsigned char const byte : id.bytes) {
        result.push_back(byte);
    }

    Utils::append(canData, result);

    return result;
}

void CANBusDataUpload::ItemData::fromJson(const Json& data)
{
    id.bits.channel = data["channel"];
    id.bits.frameType = data["frame_type"];
    id.bits.dataMethod = data["data_method"];
    id.bits.id = data["id"];
    canData = data["data"];
}

Json CANBusDataUpload::ItemData::toJson()
{
    return {{"channel", (int)id.bits.channel},
            {"frame_type", (int)id.bits.frameType},
            {"data_method", (int)id.bits.dataMethod},
            {"id", (int)id.bits.id},
            {"data", canData}};
}

}
