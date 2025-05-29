#include "JT808/MessageBody/TerminalUpgradePackageResult.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/TerminalUpgradePackage.h"
#include "JT808/Schema/TerminalUpgradePackageResultSchema.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

TerminalUpgradePackageResult::TerminalUpgradePackageResult()
    : MessageBodyBase(Schema::TerminalUpgradePackageResultSchema)
{
}

TerminalUpgradePackageResult::TerminalUpgradePackageResult(UpgradeTypes type, UpgradeResults result)
    : MessageBodyBase(Schema::TerminalUpgradePackageResultSchema)
    , m_type(type)
    , m_result(result)
{
}

void TerminalUpgradePackageResult::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalUpgradePackageResult::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    // type
    m_type = UpgradeTypes(data[pos++]);
    // result
    m_result = UpgradeResults(data[pos]);

    setIsValid(true);
}

std::vector<uint8_t> TerminalUpgradePackageResult::package()
{
    std::vector<uint8_t> result;
    // type
    result.push_back(m_type);
    // result
    result.push_back(m_result);

    return result;
}

bool TerminalUpgradePackageResult::operator==(const TerminalUpgradePackageResult& other) const
{
    return m_type == other.m_type && m_result == other.m_result;
}

void TerminalUpgradePackageResult::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_type = UpgradeTypes(data["type"]);
        m_result = UpgradeResults(data["result"]);
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json TerminalUpgradePackageResult::toJson()
{
    return {{"type", m_type}, {"result", m_result}};
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
