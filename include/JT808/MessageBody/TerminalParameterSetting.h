#ifndef TERMINALPARAMETERSETTING_H
#define TERMINALPARAMETERSETTING_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include "TerminalParameter.h"
#include <cstdint>

namespace JT808::MessageBody {

class TerminalParameterSetting : public MessageBodyBase
{
public:
    TerminalParameterSetting();
    TerminalParameterSetting(const Json& schema);
    TerminalParameterSetting(TerminalParameters params);
    TerminalParameterSetting(const Json& schema, TerminalParameters params);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalParameterSetting& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    TerminalParameters params() const;
    void setParams(const TerminalParameters& newParams);

private:
    TerminalParameters m_params;
};

}

#endif // TERMINALPARAMETERSETTING_H
