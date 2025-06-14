#ifndef TERMINALREGISTRATIONRESPONSE_H
#define TERMINALREGISTRATIONRESPONSE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>

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
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalRegistrationResponse& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

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
