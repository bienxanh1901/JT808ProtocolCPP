#include "JT808/MessageBody/TerminalUpgradePackage.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

TerminalUpgradePackage::TerminalUpgradePackage(UpgradeTypes type, const std::vector<uint8_t>& manufacturer,
                                               const std::string& version, const std::vector<uint8_t>& firmware)
    : MessageBodyBase()
    , m_type(type)
    , m_manufacturer(manufacturer)
    , m_verLen(version.length())
    , m_version(version)
    , m_fwLen(firmware.size())
    , m_firmware(firmware)
{
}

void TerminalUpgradePackage::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalUpgradePackage::parse(const uint8_t* data, int size)
{
    int pos = 0;
    m_type = UpgradeTypes(data[pos++]);

    m_manufacturer.assign(data + pos, data + pos + 5);
    pos += 5;
    m_verLen = data[pos++];

    m_version.assign(data + pos, data + pos + m_verLen);
    pos += m_verLen;

    m_fwLen = Utils::endianSwap32(data + pos);

    pos += sizeof(m_fwLen);

    if (m_fwLen != size - pos) {
        return;
    }

    for (int i = pos; i < size; i++) {
        m_firmware.push_back(data[i]);
    }

    setIsValid(true);
}

std::vector<uint8_t> TerminalUpgradePackage::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);
    result.insert(result.end(), m_manufacturer.begin(), m_manufacturer.end());
    result.push_back(m_verLen);
    result.insert(result.end(), m_version.begin(), m_version.end());
    Utils::appendU32(m_fwLen, result);
    result.insert(result.end(), m_firmware.begin(), m_firmware.end());

    return result;
}

bool TerminalUpgradePackage::operator==(const TerminalUpgradePackage& other)
{
    return m_type == other.m_type && m_manufacturer == other.m_manufacturer && m_verLen == other.m_verLen
        && m_version == other.m_version && m_fwLen == other.m_fwLen && m_firmware == other.m_firmware;
}

UpgradeTypes TerminalUpgradePackage::type() const
{
    return m_type;
}

void TerminalUpgradePackage::setType(UpgradeTypes newType)
{
    m_type = newType;
}

std::vector<uint8_t> TerminalUpgradePackage::manufacturer() const
{
    return m_manufacturer;
}

void TerminalUpgradePackage::setManufacturer(const std::vector<uint8_t>& newManufacturer)
{
    m_manufacturer = newManufacturer;
}

uint8_t TerminalUpgradePackage::verLen() const
{
    return m_verLen;
}

void TerminalUpgradePackage::setVerLen(uint8_t newVerLen)
{
    m_verLen = newVerLen;
}

std::string TerminalUpgradePackage::version() const
{
    return m_version;
}

void TerminalUpgradePackage::setVersion(const std::string& newVersion)
{
    m_version = newVersion;
}

uint32_t TerminalUpgradePackage::fwLen() const
{
    return m_fwLen;
}

void TerminalUpgradePackage::setFwLen(uint32_t newFwLen)
{
    m_fwLen = newFwLen;
}

std::vector<uint8_t> TerminalUpgradePackage::firmware() const
{
    return m_firmware;
}

void TerminalUpgradePackage::setFirmware(const std::vector<uint8_t>& newFirmware)
{
    m_firmware = newFirmware;
}

}
