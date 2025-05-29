#ifndef TERMINALUPGRADEPACKAGE_H
#define TERMINALUPGRADEPACKAGE_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

/**
 * @brief UpgradeTypes
 */
enum UpgradeTypes : uint8_t
{
    Terminal = 0,
    ICCardReader = 12,
    BDSModule = 52
};

/**
 * @brief The TerminalUpgradePackage class
 */
class TerminalUpgradePackage : public MessageBodyBase
{
public:
    TerminalUpgradePackage();
    TerminalUpgradePackage(UpgradeTypes type, std::string manufacturer, std::string version,
                           const std::vector<uint8_t>& firmware);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalUpgradePackage& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    UpgradeTypes type() const;
    void setType(UpgradeTypes newType);
    std::string manufacturer() const;
    void setManufacturer(const std::string& newManufacturer);
    std::string version() const;
    void setVersion(const std::string& newVersion);
    std::vector<uint8_t> firmware() const;
    void setFirmware(const std::vector<uint8_t>& newFirmware);

private:
    UpgradeTypes m_type = Terminal;
    std::string m_manufacturer;
    std::string m_version;
    std::vector<uint8_t> m_firmware;
};

}
#endif // TERMINALUPGRADEPACKAGE_H
