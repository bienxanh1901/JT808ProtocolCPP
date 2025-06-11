#ifndef TERMINALPARAMETERQUERY_H
#define TERMINALPARAMETERQUERY_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class TerminalParameterQuery : public MessageBodyBase
{
public:
    TerminalParameterQuery();
    TerminalParameterQuery(const std::vector<uint32_t>& ids);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalParameterQuery& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    std::vector<uint32_t> ids() const;
    void setIds(const std::vector<uint32_t>& newIds);

private:
    std::vector<uint32_t> m_ids;
};

}

#endif // TERMINALPARAMETERQUERY_H
