#include "JT808/MessageBody/TerminalRegistration.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/TerminalRegistrationSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <utility>

namespace JT808::MessageBody {

TerminalRegistration::TerminalRegistration()
    : MessageBodyBase(Schema::TerminalRegistrationSchema)
{
}

TerminalRegistration::TerminalRegistration(uint16_t province, uint16_t city, std::string manufacturer,
                                           std::string model, std::string id, LicensePlateColors color,
                                           std::string licenseNumber)
    : MessageBodyBase(Schema::TerminalRegistrationSchema)
    , m_province(province)
    , m_city(city)
    , m_manufacturer(std::move(manufacturer))
    , m_model(std::move(model))
    , m_id(std::move(id))
    , m_color(color)
    , m_licenseNumber(std::move(licenseNumber))
{
}

void TerminalRegistration::parse(const ByteArray& data)
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
    Utils::eraseTrailingNull(m_model);
    pos += 20;
    // id
    m_id.assign(data + pos, data + pos + 7);
    Utils::eraseTrailingNull(m_id);
    pos += 7;
    // license color
    m_color = LicensePlateColors(data[pos++]);
    // license number
    if (m_color != NoLicensePlate) {
        m_licenseNumber = Utils::gbkDecode(data + pos, size - pos);
    }

    setIsValid(true);
}

ByteArray TerminalRegistration::package()
{
    ByteArray result;
    // province
    Utils::appendU16(m_province, result);
    // city
    Utils::appendU16(m_city, result);
    // manufacturer
    Utils::append(m_manufacturer, result);
    // model
    Utils::append(m_model, result);
    if (m_model.length() < 20) {
        Utils::appendNull(result, 20 - m_model.length());
    }
    // id
    Utils::append(m_id, result);
    if (m_id.length() < 7) {
        Utils::appendNull(result, 7 - m_id.length());
    }
    // license plate color
    result.push_back(m_color);
    // license number
    if (m_color != NoLicensePlate) {
        Utils::appendGBK(m_licenseNumber, result);
    }

    return result;
}

bool TerminalRegistration::operator==(const TerminalRegistration& other) const
{
    return m_province == other.m_province && m_city == other.m_city && m_manufacturer == other.m_manufacturer
        && m_model == other.m_model && m_id == other.m_id && m_color == other.m_color
        && m_licenseNumber == other.m_licenseNumber;
}

void TerminalRegistration::fromJson(const Json& data)
{
    if (validate(data)) {
        m_province = data["province"];
        m_city = data["city"];
        m_manufacturer = data["manufacturer"];
        m_model = data["model"];
        m_id = data["id"];
        m_color = LicensePlateColors(data["color"]);
        m_licenseNumber = data.value("license_number", "");
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json TerminalRegistration::toJson()
{
    Json result(Json::object({{"province", m_province},
                              {"city", m_city},
                              {"manufacturer", m_manufacturer},
                              {"model", m_model},
                              {"id", m_id},
                              {"color", m_color}}));

    if (m_color != NoLicensePlate) {
        result["license_number"] = m_licenseNumber;
    }

    return result;
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

std::string TerminalRegistration::manufacturer() const
{
    return m_manufacturer;
}

void TerminalRegistration::setManufacturer(const std::string& newManufacturer)
{
    m_manufacturer = newManufacturer;
}

std::string TerminalRegistration::model() const
{
    return m_model;
}

void TerminalRegistration::setModel(const std::string& newModel)
{
    m_model = newModel;
}

std::string TerminalRegistration::id() const
{
    return m_id;
}

void TerminalRegistration::setId(const std::string& newId)
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
