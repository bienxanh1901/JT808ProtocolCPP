#ifndef TERMINALPARAMETERSETTING_H
#define TERMINALPARAMETERSETTING_H

#include "MessageBodyBase.h"
#include "TerminalParameter.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class TerminalParameterSetting : public MessageBodyBase
{
public:
    TerminalParameterSetting();
    TerminalParameterSetting(const nlohmann::json& schema);
    TerminalParameterSetting(TerminalParameters params);
    TerminalParameterSetting(const nlohmann::json& schema, TerminalParameters params);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalParameterSetting& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    TerminalParameters params() const;
    void setParams(const TerminalParameters& newParams);

private:
    TerminalParameters m_params;
};

}

#endif // TERMINALPARAMETERSETTING_H
