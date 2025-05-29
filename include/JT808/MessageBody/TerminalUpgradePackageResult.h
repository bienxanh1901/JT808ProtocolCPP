#ifndef TERMINALUPGRADEPACKAGERESULT_H
#define TERMINALUPGRADEPACKAGERESULT_H

#include "MessageBodyBase.h"
#include "TerminalUpgradePackage.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class TerminalUpgradePackageResult : public MessageBodyBase
{
public:
    /**
     * @brief UpgradeResults
     */
    enum UpgradeResults : uint8_t
    {
        Succeeded = 0,
        Failed = 1,
        Canceled = 2
    };

    TerminalUpgradePackageResult();
    TerminalUpgradePackageResult(UpgradeTypes type, UpgradeResults result);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalUpgradePackageResult& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    UpgradeTypes type() const;
    void setType(UpgradeTypes newType);
    UpgradeResults result() const;
    void setResult(UpgradeResults newResult);

private:
    UpgradeTypes m_type = Terminal;
    UpgradeResults m_result = Succeeded;
};

}
#endif // TERMINALUPGRADEPACKAGERESULT_H
