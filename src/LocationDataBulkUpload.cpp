#include "JT808/MessageBody/LocationDataBulkUpload.h"

namespace JT808::MessageBody {

LocationDataBulkUpload::LocationDataBulkUpload(DataType type, const std::vector<LocationInformation>& locations)
    : MessageBodyBase()
    , m_type(type)
    , m_locations(locations)
{
}

void LocationDataBulkUpload::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void LocationDataBulkUpload::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // length
    uint16_t length = Utils::endianSwap16(data + pos);
    pos += sizeof(length);
    // type
    m_type = DataType(data[pos++]);
    // locations
    for (int i = 0; i < length; i++) {
        uint16_t itemLength = Utils::endianSwap16(data + pos);
        LocationInformation item;
        pos += sizeof(itemLength);
        item.parse(data + pos, itemLength);
        pos += itemLength;
        m_locations.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> LocationDataBulkUpload::package()
{
    std::vector<uint8_t> result;
    // length
    Utils::appendU16(m_locations.size(), result);
    // type
    result.push_back(m_type);
    // locations
    for (auto& item : m_locations) {
        std::vector<uint8_t> itemData(item.package());
        Utils::appendU16(itemData.size(), result);
        Utils::append(itemData, result);
    }

    return result;
}

bool LocationDataBulkUpload::operator==(const LocationDataBulkUpload& other) const
{
    return m_type == other.m_type && m_locations == other.m_locations;
}

LocationDataBulkUpload::DataType LocationDataBulkUpload::type() const
{
    return m_type;
}

void LocationDataBulkUpload::setType(DataType newType)
{
    m_type = newType;
}

std::vector<LocationInformation> LocationDataBulkUpload::locations() const
{
    return m_locations;
}

void LocationDataBulkUpload::setLocations(const std::vector<LocationInformation>& newLocations)
{
    m_locations = newLocations;
}
}
