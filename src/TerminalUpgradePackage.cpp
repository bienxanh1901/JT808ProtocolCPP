#include "JT808/MessageBody/TerminalUpgradePackage.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

TerminalUpgradePackage::TerminalUpgradePackage()
    : MessageBodyBase({})
{
}

TerminalUpgradePackage::TerminalUpgradePackage(UpgradeTypes type, std::string manufacturer, std::string version,
                                               std::string firmware)
    : MessageBodyBase({})
    , m_type(type)
    , m_manufacturer(std::move(manufacturer))
    , m_version(std::move(version))
    , m_firmware(std::move(firmware))
{
}

void TerminalUpgradePackage::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalUpgradePackage::parse(const uint8_t* data, int size)
{
    int pos = 0;
    uint32_t length = 0;
    // type
    m_type = UpgradeTypes(data[pos++]);
    // manufacturer()
    m_manufacturer.assign(data + pos, data + pos + 5);
    pos += 5;
    // version length
    length = data[pos++];
    // version
    m_version.assign(data + pos, data + pos + length);
    pos += length;
    // firmware length
    length = Utils::endianSwap32(data + pos);
    pos += sizeof(length);
    if (length != size - pos) {
        return;
    }
    // firmware
    m_firmware.assign(data + pos, data + size);

    setIsValid(true);
}

std::vector<uint8_t> TerminalUpgradePackage::package()
{
    std::vector<uint8_t> result;
    // type
    result.push_back(m_type);
    // manufacturer()
    Utils::append(m_manufacturer, result);
    // version length
    result.push_back(m_version.size());
    // version
    Utils::append(m_version, result);
    // firmware length
    Utils::appendU32(m_firmware.size(), result);
    // firmware
    Utils::append(m_firmware, result);

    return result;
}

bool TerminalUpgradePackage::operator==(const TerminalUpgradePackage& other) const
{
    return m_type == other.m_type && m_manufacturer == other.m_manufacturer && m_version == other.m_version
        && m_firmware == other.m_firmware;
}

void TerminalUpgradePackage::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_type = UpgradeTypes(data["type"]);
        m_manufacturer = data["manufacturer"];
        if (data["ver_len"] > 0) {
            m_version = data["version"];
        }
        if (data["fw_len"] > 0) {
            m_firmware = data["firmware"];
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json TerminalUpgradePackage::toJson()
{
    return {
        {"type", m_type},       {"manufacturer", m_manufacturer}, {"ver_len", m_version.length()},
        {"version", m_version}, {"fw_len", m_firmware.length()},  {"firmware", m_firmware},
    };
}

UpgradeTypes TerminalUpgradePackage::type() const
{
    return m_type;
}

void TerminalUpgradePackage::setType(UpgradeTypes newType)
{
    m_type = newType;
}

std::string TerminalUpgradePackage::manufacturer() const
{
    return m_manufacturer;
}

void TerminalUpgradePackage::setManufacturer(const std::string& newManufacturer)
{
    m_manufacturer = newManufacturer;
}

std::string TerminalUpgradePackage::version() const
{
    return m_version;
}

void TerminalUpgradePackage::setVersion(const std::string& newVersion)
{
    m_version = newVersion;
}

std::string TerminalUpgradePackage::firmware() const
{
    return m_firmware;
}

void TerminalUpgradePackage::setFirmware(const std::string& newFirmware)
{
    m_firmware = newFirmware;
}

}
