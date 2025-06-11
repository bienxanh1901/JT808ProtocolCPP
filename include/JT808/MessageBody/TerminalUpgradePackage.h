#ifndef TERMINALUPGRADEPACKAGE_H
#define TERMINALUPGRADEPACKAGE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>

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
    TerminalUpgradePackage(UpgradeTypes type, std::string manufacturer, std::string version, const ByteArray& firmware);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalUpgradePackage& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    UpgradeTypes type() const;
    void setType(UpgradeTypes newType);
    std::string manufacturer() const;
    void setManufacturer(const std::string& newManufacturer);
    std::string version() const;
    void setVersion(const std::string& newVersion);
    ByteArray firmware() const;
    void setFirmware(const ByteArray& newFirmware);

private:
    UpgradeTypes m_type = Terminal;
    std::string m_manufacturer;
    std::string m_version;
    ByteArray m_firmware;
};

}
#endif // TERMINALUPGRADEPACKAGE_H
