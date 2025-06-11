#ifndef TERMINALAUTHENTICATION_H
#define TERMINALAUTHENTICATION_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

/**
 * @brief The TerminalAuthentication class
 */
class TerminalAuthentication : public MessageBodyBase
{
public:
    TerminalAuthentication();
    TerminalAuthentication(std::string authCode);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalAuthentication& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    std::string authCode() const;
    void setAuthCode(const std::string& newAuthCode);

private:
    std::string m_authCode;
};

}

#endif // TERMINALAUTHENTICATION_H
