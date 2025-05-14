#ifndef TERMINALREGISTRATIONRESPONSE_H
#define TERMINALREGISTRATIONRESPONSE_H

#include "MessageBodyBase.h"
#include <stdint.h>
#include <string>

namespace JT808 {
namespace MessageBody {

/**
 * @brief The TerminalRegistrationResponse class
 */
class TerminalRegistrationResponse : public MessageBodyBase
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

    TerminalRegistrationResponse(const std::vector<uint8_t>& data = {});
    TerminalRegistrationResponse(uint8_t* data, int size);

    void parse() override;
    void package() override;

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);
    ResponseResults result() const;
    void setResult(ResponseResults newResult);
    std::string authCode() const;
    void setAuthCode(const std::string& newAuthCode);

private:
    uint16_t m_seq = 0;
    ResponseResults m_result = Succeeded;
    std::string m_authCode = "";
};

}
}

#endif // TERMINALREGISTRATIONRESPONSE_H
