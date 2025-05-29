#include "JT808/MessageBody/LocationDataBulkUpload.h"
#include "JT808/MessageBody/LocationInformation.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/LocationDataBulkUploadSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

LocationDataBulkUpload::LocationDataBulkUpload()
    : MessageBodyBase(Schema::LocationDataBulkUploadSchema)
{
}

LocationDataBulkUpload::LocationDataBulkUpload(DataType type, const std::vector<LocationInformation>& locations)
    : MessageBodyBase(Schema::LocationDataBulkUploadSchema)
    , m_type(type)
    , m_locations(locations)
{
}

void LocationDataBulkUpload::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void LocationDataBulkUpload::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    // length
    uint16_t const length = Utils::endianSwap16(data + pos);
    pos += sizeof(length);
    // type
    m_type = DataType(data[pos++]);
    // locations
    for (int i = 0; i < length; i++) {
        uint16_t const itemLength = Utils::endianSwap16(data + pos);
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
        std::vector<uint8_t> const itemData(item.package());
        Utils::appendU16(itemData.size(), result);
        Utils::append(itemData, result);
    }

    return result;
}

bool LocationDataBulkUpload::operator==(const LocationDataBulkUpload& other) const
{
    return m_type == other.m_type && m_locations == other.m_locations;
}

void LocationDataBulkUpload::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_type = DataType(data["type"]);

        if (data["length"] > 0) {
            for (auto& location : data["locations"]) {
                LocationInformation item;
                item.fromJson(location);
                m_locations.push_back(item);
            }
        }

        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json LocationDataBulkUpload::toJson()
{
    nlohmann::json result({{"type", m_type}, {"length", m_locations.size()}, {"locations", {}}});

    for (auto& item : m_locations) {
        result["locations"].push_back(item.toJson());
    }

    return result;
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
