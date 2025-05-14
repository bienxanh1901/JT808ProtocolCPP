#ifndef TERMINALPARAMETERQUERY_H
#define TERMINALPARAMETERQUERY_H

#include "MessageBodyBase.h"
#include <stdint.h>
#include <vector>

namespace JT808 {

namespace MessageBody {

class TerminalParameterQuery : public MessageBodyBase
{
public:
    TerminalParameterQuery(const std::vector<uint8_t>& data = {});
    TerminalParameterQuery(uint8_t* data, int size);

    void parse() override;
    void package() override;

    uint8_t length() const;
    void setLength(uint8_t newLength);
    std::vector<uint32_t> ids() const;
    void setIds(const std::vector<uint32_t>& newIds);

private:
    uint8_t m_length;
    std::vector<uint32_t> m_ids;
};

}
}

#endif // TERMINALPARAMETERQUERY_H
