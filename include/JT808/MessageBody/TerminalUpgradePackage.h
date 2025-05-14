#ifndef TERMINALUPGRADE_H
#define TERMINALUPGRADE_H

#include "MessageBodyBase.h"

#include <stdint.h>
#include <string>
#include <vector>

namespace JT808 {
namespace MessageBody {

/**
 * @brief UpgradeTypes
 */
typedef enum
{
    Terminal = 0,
    ICCardReader = 12,
    BDSModule = 52
} UpgradeTypes;

/**
 * @brief The TerminalUpgradePackage class
 */
class TerminalUpgradePackage : public MessageBodyBase
{
public:
    TerminalUpgradePackage(const std::vector<uint8_t>& data = {});
    TerminalUpgradePackage(uint8_t* data, int size);

    void parse() override;
    void package() override;

    UpgradeTypes type() const;
    void setType(UpgradeTypes newType);
    std::vector<uint8_t> manufacturer() const;
    void setManufacturer(const std::vector<uint8_t>& newManufacturer);
    uint8_t verLen() const;
    void setVerLen(uint8_t newVerLen);
    std::string version() const;
    void setVersion(const std::string& newVersion);
    uint32_t fwLen() const;
    void setFwLen(uint32_t newFwLen);
    std::vector<uint8_t> firmware() const;
    void setFirmware(const std::vector<uint8_t>& newFirmware);

private:
    UpgradeTypes m_type = Terminal;
    std::vector<uint8_t> m_manufacturer = {};
    uint8_t m_verLen = 0;
    std::string m_version = "";
    uint32_t m_fwLen = 0;
    std::vector<uint8_t> m_firmware = {};
};

}
}
#endif // TERMINALUPGRADE_H
