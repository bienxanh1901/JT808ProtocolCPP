#include "JT808/MessageBody/TerminalUpgradePackageResult.h"

namespace JT808 {
namespace MessageBody {
TerminalUpgradePackageResult::TerminalUpgradePackageResult(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

TerminalUpgradePackageResult::TerminalUpgradePackageResult(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void TerminalUpgradePackageResult::parse()
{
    uint8_t* data = m_rawData.data();
    int pos = 0;

    m_type = UpgradeTypes(data[pos++]);
    m_result = UpgradeResults(data[pos]);

    m_isValid = true;
}

void TerminalUpgradePackageResult::package()
{
    m_rawData.clear();

    m_rawData.push_back(m_type);
    m_rawData.push_back(m_result);

    m_isValid = true;
}

UpgradeTypes TerminalUpgradePackageResult::type() const
{
    return m_type;
}

void TerminalUpgradePackageResult::setType(UpgradeTypes newType)
{
    m_type = newType;
}

TerminalUpgradePackageResult::UpgradeResults TerminalUpgradePackageResult::result() const
{
    return m_result;
}

void TerminalUpgradePackageResult::setResult(UpgradeResults newResult)
{
    m_result = newResult;
}

}
}
