#ifndef TERMINALREGISTRATIONRESPONSE_H
#define TERMINALREGISTRATIONRESPONSE_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

/**
 * @brief The TerminalRegistrationResponse class
 */
class TerminalRegistrationResponse : public MessageBodyBase
{
public:
    /**
     * @brief RegistrationResponseResults
     */
    enum ResponseResults : uint8_t
    {
        Succeeded = 0,
        VehicleExisted = 1,
        VehicleNotFound = 2,
        TerminalExisted = 3,
        TerminalNotFound = 4,
    };

    TerminalRegistrationResponse();
    TerminalRegistrationResponse(uint16_t seq, ResponseResults result, std::string authCode = "");
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalRegistrationResponse& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    ResponseResults result() const;
    void setResult(ResponseResults newResult);
    std::string authCode() const;
    void setAuthCode(const std::string& newAuthCode);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

private:
    uint16_t m_seq = 0;
    ResponseResults m_result = Succeeded;
    std::string m_authCode;
};

}

#endif // TERMINALREGISTRATIONRESPONSE_H
