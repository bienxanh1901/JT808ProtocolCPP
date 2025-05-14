#ifndef TERMINALPARAMETERSETTING_H
#define TERMINALPARAMETERSETTING_H

#include "MessageBodyBase.h"
#include "TerminalParameter.h"

#include <stdint.h>
#include <vector>

namespace JT808 {

namespace MessageBody {

class TerminalParameterSetting : public MessageBodyBase
{
public:
    TerminalParameterSetting(const std::vector<uint8_t>& data = {});
    TerminalParameterSetting(uint8_t* data, int size);

    void parse() override;
    void package() override;

    uint8_t length() const;
    void setLength(uint8_t newLength);
    TerminalParameters params() const;
    void setParams(const TerminalParameters& newParams);

private:
    uint8_t m_length;
    TerminalParameters m_params;
};

}
}

#endif // TERMINALPARAMETERSETTING_H
