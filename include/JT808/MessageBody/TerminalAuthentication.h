#ifndef TERMINALAUTHENTICATION_H
#define TERMINALAUTHENTICATION_H

#include "MessageBodyBase.h"
#include <string>

namespace JT808 {
namespace MessageBody {

/**
 * @brief The TerminalAuthentication class
 */
class TerminalAuthentication : public MessageBodyBase
{
public:
    TerminalAuthentication(const std::vector<uint8_t>& data = {});
    TerminalAuthentication(uint8_t* data, int size);

    void parse() override;
    void package() override;

    std::string authCode() const;
    void setAuthCode(const std::string& newAuthCode);

private:
    std::string m_authCode;
};

}
}

#endif // TERMINALAUTHENTICATION_H
