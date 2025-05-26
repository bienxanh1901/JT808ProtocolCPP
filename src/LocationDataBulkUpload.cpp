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
    uint16_t length = Utils::endianSwap16(data + pos);
    pos += sizeof(length);

    m_type = DataType(data[pos++]);

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

    Utils::appendU16(m_locations.size(), result);
    result.push_back(m_type);

    for (auto& item : m_locations) {
        std::vector<uint8_t> itemData(item.package());
        Utils::appendU16(itemData.size(), result);
        result.insert(result.end(), itemData.begin(), itemData.end());
    }

    return result;
}

bool LocationDataBulkUpload::operator==(const LocationDataBulkUpload& other)
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
