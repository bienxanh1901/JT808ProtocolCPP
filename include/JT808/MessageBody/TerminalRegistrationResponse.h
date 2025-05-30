#ifndef TERMINALREGISTRATIONRESPONSE_H
#define TERMINALREGISTRATIONRESPONSE_H

#include "SequenceMessageBodyBase.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

/**
 * @brief The TerminalRegistrationResponse class
 */
class TerminalRegistrationResponse : public SequenceMessageBodyBase
{
public:
    /**
     * @brief RegistrationResponseResults
     */
    typedef enum
    {
        Succeeded = 0,
        VehicleExisted = 1,
        VehicleNotFound = 2,
        TerminalExisted = 3,
        TerminalNotFound = 4,
    } ResponseResults;

    TerminalRegistrationResponse() = default;
    TerminalRegistrationResponse(uint16_t seq, ResponseResults result, const std::string& authCode = "");
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalRegistrationResponse& other);

    ResponseResults result() const;
    void setResult(ResponseResults newResult);
    std::string authCode() const;
    void setAuthCode(const std::string& newAuthCode);

private:
    ResponseResults m_result = Succeeded;
    std::string m_authCode = "";
};

}

#endif // TERMINALREGISTRATIONRESPONSE_H
