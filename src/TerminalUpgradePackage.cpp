#include "JT808/MessageBody/TerminalUpgradePackage.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {
TerminalUpgradePackage::TerminalUpgradePackage(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

TerminalUpgradePackage::TerminalUpgradePackage(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void TerminalUpgradePackage::parse()
{
    uint8_t* data = m_rawData.data();
    int pos = 0;
    m_type = UpgradeTypes(data[pos++]);

    m_manufacturer.assign(data + pos, data + pos + 5);
    pos += 5;
    m_verLen = data[pos++];

    m_version.assign(data + pos, data + pos + m_verLen);
    pos += m_verLen;

    m_fwLen = Utils::endianSwap32(data + pos);

    pos += sizeof(m_fwLen);

    if (m_fwLen != m_rawData.size() - pos) {
        return;
    }

    for (int i = pos; i < m_rawData.size(); i++) {
        m_firmware.push_back(data[i]);
    }

    m_isValid = true;
}

void TerminalUpgradePackage::package()
{
    Utils::U32Array u32Data = {0};

    m_rawData.clear();

    m_rawData.push_back(m_type);

    m_rawData.insert(m_rawData.end(), m_manufacturer.begin(), m_manufacturer.end());

    m_rawData.push_back(m_verLen);
    m_rawData.insert(m_rawData.end(), m_version.begin(), m_version.end());

    u32Data.value = Utils::endianSwap32(m_fwLen);
    m_rawData.insert(m_rawData.end(), u32Data.array, u32Data.array + sizeof(u32Data));

    m_rawData.insert(m_rawData.end(), m_firmware.begin(), m_firmware.end());

    m_isValid = true;
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
}
