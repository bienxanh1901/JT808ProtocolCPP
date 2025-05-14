#ifndef TERMINALUPGRADERESULT_H
#define TERMINALUPGRADERESULT_H

#include "MessageBodyBase.h"
#include "TerminalUpgradePackage.h"

#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class TerminalUpgradePackageResult : public MessageBodyBase
{
public:
    /**
     * @brief UpgradeResults
     */
    typedef enum
    {
        Succeeded = 0,
        Failed = 1,
        Canceled = 2
    } UpgradeResults;

    TerminalUpgradePackageResult() = default;
    TerminalUpgradePackageResult(UpgradeTypes type, UpgradeResults result);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalUpgradePackageResult& other);

    UpgradeTypes type() const;
    void setType(UpgradeTypes newType);
    UpgradeResults result() const;
    void setResult(UpgradeResults newResult);

private:
    UpgradeTypes m_type;
    UpgradeResults m_result = Succeeded;
};

}
#endif // TERMINALUPGRADERESULT_H
