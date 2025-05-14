#ifndef TERMINALPARAMETERSETTING_H
#define TERMINALPARAMETERSETTING_H

#include "MessageBodyBase.h"
#include "TerminalParameter.h"

#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class TerminalParameterSetting : public MessageBodyBase
{
public:
    TerminalParameterSetting() = default;
    TerminalParameterSetting(const TerminalParameters& params);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalParameterSetting& other);

    uint8_t length() const;
    void setLength(uint8_t newLength);
    TerminalParameters params() const;
    void setParams(const TerminalParameters& newParams);

private:
    uint8_t m_length;
    TerminalParameters m_params;
};

}

#endif // TERMINALPARAMETERSETTING_H
