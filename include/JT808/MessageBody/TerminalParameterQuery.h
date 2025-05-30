#ifndef TERMINALPARAMETERQUERY_H
#define TERMINALPARAMETERQUERY_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class TerminalParameterQuery : public MessageBodyBase
{
public:
    TerminalParameterQuery() = default;
    TerminalParameterQuery(const std::vector<uint32_t>& ids);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalParameterQuery& other);

    uint8_t length() const;
    void setLength(uint8_t newLength);
    std::vector<uint32_t> ids() const;
    void setIds(const std::vector<uint32_t>& newIds);

private:
    uint8_t m_length;
    std::vector<uint32_t> m_ids;
};

}

#endif // TERMINALPARAMETERQUERY_H
