#include "JT808/MessageBody/TerminalRegistration.h"
#include "JT808/Utils.h"
#include <cstring>

namespace JT808::MessageBody {

TerminalRegistration::TerminalRegistration(uint16_t province, uint16_t city, const std::vector<uint8_t>& manufacturer,
                                           const std::vector<uint8_t>& model, const std::vector<uint8_t>& id,
                                           LicensePlateColors color, const std::string& vin)
    : MessageBodyBase()
    , m_province(std::move(province))
    , m_city(std::move(city))
    , m_manufacturer(manufacturer)
    , m_model(model)
    , m_id(id)
    , m_color(color)
    , m_vin(vin)
{
}

void TerminalRegistration::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalRegistration::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_province = Utils::endianSwap16(data);
    pos += sizeof(m_province);
    m_city = Utils::endianSwap16(data + pos);
    pos += sizeof(m_city);
    m_manufacturer.assign(data + pos, data + pos + 5);
    pos += 5;
    m_model.assign(data + pos, data + pos + 20);
    pos += 20;
    m_id.assign(data + pos, data + pos + 7);
    pos += 7;
    m_color = LicensePlateColors(data[pos++]);

    if (m_color != NoLicensePlate) {
        for (int i = pos; i < size; i++) {
            m_vin.push_back(data[i]);
        }
    }

    setIsValid(true);
}

std::vector<uint8_t> TerminalRegistration::package()
{
    std::vector<uint8_t> result;

    Utils::appendU16(m_province, result);
    Utils::appendU16(m_city, result);
    result.insert(result.end(), m_manufacturer.begin(), m_manufacturer.end());
    result.insert(result.end(), m_model.begin(), m_model.end());
    result.insert(result.end(), m_id.begin(), m_id.end());

    result.push_back(m_color);

    if (m_color != NoLicensePlate) {
        result.insert(result.end(), m_vin.begin(), m_vin.end());
    }

    return result;
}

bool TerminalRegistration::operator==(const TerminalRegistration& other)
{
    return m_province == other.m_province && m_city == other.m_city && m_manufacturer == other.m_manufacturer
        && m_model == other.m_model && m_id == other.m_id && m_color == other.m_color && m_vin == other.m_vin;
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

std::string TerminalRegistration::vin() const
{
    return m_vin;
}

void TerminalRegistration::setVin(const std::string& newVin)
{
    m_vin = newVin;
}

}
