#ifndef TERMINALPARAMETERQUERYRESPONSE_H
#define TERMINALPARAMETERQUERYRESPONSE_H

#include "TerminalParameter.h"
#include "TerminalParameterSetting.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class TerminalParameterQueryResponse : public TerminalParameterSetting
{
public:
    TerminalParameterQueryResponse() = default;
    TerminalParameterQueryResponse(uint16_t seq, const TerminalParameters& params);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalParameterQueryResponse& other);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
};

}

#endif // TERMINALPARAMETERQUERYRESPONSE_H
