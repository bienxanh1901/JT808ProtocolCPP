#ifndef TERMINALPARAMETERQUERYRESPONSE_H
#define TERMINALPARAMETERQUERYRESPONSE_H

#include "JT808/Common.h"
#include "TerminalParameter.h"
#include "TerminalParameterSetting.h"
#include <cstdint>

namespace JT808::MessageBody {

class TerminalParameterQueryResponse : public TerminalParameterSetting
{
public:
    TerminalParameterQueryResponse();
    TerminalParameterQueryResponse(uint16_t seq, const TerminalParameters& params);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalParameterQueryResponse& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
};

}

#endif // TERMINALPARAMETERQUERYRESPONSE_H
