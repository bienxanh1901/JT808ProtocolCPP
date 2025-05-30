#include "JT808/MessageBody/TerminalUpgradePackageResult.h"

namespace JT808::MessageBody {

TerminalUpgradePackageResult::TerminalUpgradePackageResult(UpgradeTypes type, UpgradeResults result)
    : MessageBodyBase()
    , m_type(type)
    , m_result(result)
{
}

void TerminalUpgradePackageResult::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalUpgradePackageResult::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_type = UpgradeTypes(data[pos++]);
    m_result = UpgradeResults(data[pos]);

    setIsValid(true);
}

std::vector<uint8_t> TerminalUpgradePackageResult::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);
    result.push_back(m_result);

    return result;
}

bool TerminalUpgradePackageResult::operator==(const TerminalUpgradePackageResult& other)
{
    return m_type == other.m_type && m_result == other.m_result;
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
