#ifndef TERMINALUPGRADEPACKAGERESULT_H
#define TERMINALUPGRADEPACKAGERESULT_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include "TerminalUpgradePackage.h"
#include <cstdint>

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
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalUpgradePackageResult& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

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
