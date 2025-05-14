#include "JT808/MessageBody/TerminalRegistration.h"
#include "JT808/Utils.h"
#include <cstring>

namespace JT808 {
namespace MessageBody {

TerminalRegistration::TerminalRegistration(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

TerminalRegistration::TerminalRegistration(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void TerminalRegistration::parse()
{
    uint8_t* data = m_rawData.data();
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
        for (int i = pos; i < m_rawData.size(); i++) {
            m_vin.push_back(data[i]);
        }
    }

    m_isValid = true;
}

void TerminalRegistration::package()
{
    Utils::U16Array u16Data = {0};

    m_rawData.clear();

    u16Data.value = Utils::endianSwap16(m_province);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    u16Data.value = Utils::endianSwap16(m_city);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    m_rawData.insert(m_rawData.end(), m_manufacturer.begin(), m_manufacturer.end());
    m_rawData.insert(m_rawData.end(), m_model.begin(), m_model.end());
    m_rawData.insert(m_rawData.end(), m_id.begin(), m_id.end());

    m_rawData.push_back(m_color);

    if (m_color != NoLicensePlate) {
        m_rawData.insert(m_rawData.end(), m_vin.begin(), m_vin.end());
    }

    m_isValid = true;
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
}
