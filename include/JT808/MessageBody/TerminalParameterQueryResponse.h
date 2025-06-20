#ifndef TERMINALPARAMETERQUERYRESPONSE_H
#define TERMINALPARAMETERQUERYRESPONSE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include "TerminalParameter.h"
#include <cstdint>

namespace JT808::MessageBody {

class TerminalParameterQueryResponse : public MessageBodyBase
{
public:
    TerminalParameterQueryResponse();
    TerminalParameterQueryResponse(const uint8_t* data, int size);
    TerminalParameterQueryResponse(const Json& data);
    TerminalParameterQueryResponse(uint16_t seq, const TerminalParameters& params);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalParameterQueryResponse& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

    TerminalParameters params() const;
    void setParams(const TerminalParameters& newParams);

private:
    uint16_t m_seq = 0;
    TerminalParameters m_params;
};

}

#endif // TERMINALPARAMETERQUERYRESPONSE_H
