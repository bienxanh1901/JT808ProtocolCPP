#ifndef TERMINALREGISTRATION_H
#define TERMINALREGISTRATION_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

/**
 * @brief LicensePlateColors
 */
enum LicensePlateColors : uint8_t
{
    NoLicensePlate = 0,
    Blue = 1,
    Yellow = 2,
    Black = 3,
    White = 4,
    Green = 5,
    Other = 9
};

/**
 * @brief The TerminalRegistration class
 */
class TerminalRegistration : public MessageBodyBase
{
public:
    TerminalRegistration();
    TerminalRegistration(uint16_t province, uint16_t city, std::string manufacturer, std::string model, std::string id,
                         LicensePlateColors color, std::string licenseNumber);

    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalRegistration& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint16_t province() const;
    void setProvince(uint16_t newProvince);
    uint16_t city() const;
    void setCity(uint16_t newCity);
    std::string manufacturer() const;
    void setManufacturer(const std::string& newManufacturer);
    std::string model() const;
    void setModel(const std::string& newModel);
    std::string id() const;
    void setId(const std::string& newId);
    LicensePlateColors color() const;
    void setColor(LicensePlateColors newColor);
    std::string licenseNumber() const;
    void setLicenseNumber(const std::string& newLicenseNumber);

private:
    uint16_t m_province = 0;
    uint16_t m_city = 0;
    std::string m_manufacturer;
    std::string m_model;
    std::string m_id;
    LicensePlateColors m_color = NoLicensePlate;
    std::string m_licenseNumber;
};

}

#endif // TERMINALREGISTRATION_H
