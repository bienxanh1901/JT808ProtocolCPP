#ifndef TERMINALPARAMETERQUERYRESPONSE_H
#define TERMINALPARAMETERQUERYRESPONSE_H

#include "MessageBodyBase.h"
#include "TerminalParameter.h"
#include <stdint.h>
#include <vector>

namespace JT808 {
namespace MessageBody {

class TerminalParameterQueryResponse : public MessageBodyBase
{
public:
    TerminalParameterQueryResponse(const std::vector<uint8_t>& data = {});
    TerminalParameterQueryResponse(uint8_t* data, int size);

    void parse() override;
    void package() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);
    uint8_t length() const;
    void setLength(uint8_t newLength);
    TerminalParameters params() const;
    void setParams(const TerminalParameters& newParams);

private:
    uint16_t m_seq;
    uint8_t m_length;
    TerminalParameters m_params;
};

}
}

#endif // TERMINALPARAMETERQUERYRESPONSE_H
