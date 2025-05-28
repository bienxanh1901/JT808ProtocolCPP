#include "JT808/MessageBody/TerminalRegistration.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

TerminalRegistration::TerminalRegistration(uint16_t province, uint16_t city, const std::vector<uint8_t>& manufacturer,
                                           const std::vector<uint8_t>& model, const std::vector<uint8_t>& id,
                                           LicensePlateColors color, std::string licenseNumber)
    : m_province(province)
    , m_city(city)
    , m_manufacturer(manufacturer)
    , m_model(model)
    , m_id(id)
    , m_color(color)
    , m_licenseNumber(std::move(licenseNumber))
{
}

void TerminalRegistration::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalRegistration::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // province
    m_province = Utils::endianSwap16(data);
    pos += sizeof(m_province);
    // city
    m_city = Utils::endianSwap16(data + pos);
    pos += sizeof(m_city);
    // manufacturer
    m_manufacturer.assign(data + pos, data + pos + 5);
    pos += 5;
    // model
    m_model.assign(data + pos, data + pos + 20);
    pos += 20;
    // id
    m_id.assign(data + pos, data + pos + 7);
    pos += 7;
    // license color
    m_color = LicensePlateColors(data[pos++]);
    // license number
    if (m_color != NoLicensePlate) {
        m_licenseNumber.assign(data + pos, data + size);
    }

    setIsValid(true);
}

std::vector<uint8_t> TerminalRegistration::package()
{
    std::vector<uint8_t> result;
    // province
    Utils::appendU16(m_province, result);
    // city
    Utils::appendU16(m_city, result);
    // manufacturer
    Utils::append(m_manufacturer, result);
    // model
    Utils::append(m_model, result);
    // id
    Utils::append(m_id, result);
    // license plate color
    result.push_back(m_color);
    // license number
    if (m_color != NoLicensePlate) {
        Utils::append(m_licenseNumber, result);
    }

    return result;
}

bool TerminalRegistration::operator==(const TerminalRegistration& other) const
{
    return m_province == other.m_province && m_city == other.m_city && m_manufacturer == other.m_manufacturer
        && m_model == other.m_model && m_id == other.m_id && m_color == other.m_color
        && m_licenseNumber == other.m_licenseNumber;
}

uint16_t TerminalRegistration::province() const
{
    return m_province;
}

void TerminalRegistration::setProvince(uint16_t newProvince)
{
    m_province = newProvince;
}

uint16_t TerminalRegistration::city() const
{
    return m_city;
}

void TerminalRegistration::setCity(uint16_t newCity)
{
    m_city = newCity;
}

std::vector<uint8_t> TerminalRegistration::manufacturer() const
{
    return m_manufacturer;
}

void TerminalRegistration::setManufacturer(const std::vector<uint8_t>& newManufacturer)
{
    m_manufacturer = newManufacturer;
}

std::vector<uint8_t> TerminalRegistration::model() const
{
    return m_model;
}

void TerminalRegistration::setModel(const std::vector<uint8_t>& newModel)
{
    m_model = newModel;
}

std::vector<uint8_t> TerminalRegistration::id() const
{
    return m_id;
}

void TerminalRegistration::setId(const std::vector<uint8_t>& newId)
{
    m_id = newId;
}

LicensePlateColors TerminalRegistration::color() const
{
    return m_color;
}

void TerminalRegistration::setColor(LicensePlateColors newColor)
{
    m_color = newColor;
}

std::string TerminalRegistration::licenseNumber() const
{
    return m_licenseNumber;
}

void TerminalRegistration::setLicenseNumber(const std::string& newLicenseNumber)
{
    m_licenseNumber = newLicenseNumber;
}

}
