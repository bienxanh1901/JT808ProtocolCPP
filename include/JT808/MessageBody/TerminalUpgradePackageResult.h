#ifndef TERMINALUPGRADERESULT_H
#define TERMINALUPGRADERESULT_H

#include "MessageBodyBase.h"
#include "TerminalUpgradePackage.h"

#include <stdint.h>
#include <vector>

namespace JT808 {
namespace MessageBody {

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

    TerminalUpgradePackageResult(const std::vector<uint8_t>& data = {});
    TerminalUpgradePackageResult(uint8_t* data, int size);

    void parse() override;
    void package() override;

    UpgradeTypes type() const;
    void setType(UpgradeTypes newType);
    UpgradeResults result() const;
    void setResult(UpgradeResults newResult);

private:
    UpgradeTypes m_type;
    UpgradeResults m_result = Succeeded;
};

}
}
#endif // TERMINALUPGRADERESULT_H
