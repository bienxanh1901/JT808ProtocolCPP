#ifndef TERMINALAUTHENTICATION_H
#define TERMINALAUTHENTICATION_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

namespace JT808::MessageBody {

/**
 * @brief The TerminalAuthentication class
 */
class TerminalAuthentication : public MessageBodyBase
{
public:
    TerminalAuthentication() = default;
    TerminalAuthentication(std::string authCode);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalAuthentication& other) const;

    std::string authCode() const;
    void setAuthCode(const std::string& newAuthCode);

private:
    std::string m_authCode;
};

}

#endif // TERMINALAUTHENTICATION_H
