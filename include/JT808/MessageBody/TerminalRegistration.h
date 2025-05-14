#ifndef TERMINALREGISTRATION_H
#define TERMINALREGISTRATION_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

/**
 * @brief LicensePlateColors
 */
typedef enum
{
    NoLicensePlate = 0,
    Blue = 1,
    Yellow = 2,
    Black = 3,
    White = 4,
    Green = 5,
    Other = 9
} LicensePlateColors;

/**
 * @brief The TerminalRegistration class
 */
class TerminalRegistration : public MessageBodyBase
{
public:
    TerminalRegistration() = default;
    TerminalRegistration(uint16_t province, uint16_t city, const std::vector<uint8_t>& manufacturer,
                         const std::vector<uint8_t>& model, const std::vector<uint8_t>& id, LicensePlateColors color,
                         const std::string& vin);

    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalRegistration& other);

    uint16_t province() const;
    void setProvince(uint16_t newProvince);
    uint16_t city() const;
    void setCity(uint16_t newCity);
    std::vector<uint8_t> manufacturer() const;
    void setManufacturer(const std::vector<uint8_t>& newManufacturer);
    std::vector<uint8_t> model() const;
    void setModel(const std::vector<uint8_t>& newModel);
    std::vector<uint8_t> id() const;
    void setId(const std::vector<uint8_t>& newId);
    LicensePlateColors color() const;
    void setColor(LicensePlateColors newColor);
    std::string vin() const;
    void setVin(const std::string& newVin);

private:
    uint16_t m_province = 0;
    uint16_t m_city = 0;
    std::vector<uint8_t> m_manufacturer;
    std::vector<uint8_t> m_model;
    std::vector<uint8_t> m_id;
    LicensePlateColors m_color = NoLicensePlate;
    std::string m_vin = "";
};

}

#endif // TERMINALREGISTRATION_H
