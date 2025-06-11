#ifndef TEXTMESSAGEDISPATCH_H
#define TEXTMESSAGEDISPATCH_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

class TextMessageDispatch : public MessageBodyBase
{
public:
    union Flag {
        struct
        {
            uint8_t sos : 1;
            uint8_t reserved : 1;
            uint8_t terminalDisplay : 1;
            uint8_t terminalTTS : 1;
            uint8_t advDisplay : 1;
            uint8_t infoType : 1; // 0 navigation information, 1 CAN Fault Code
            uint8_t reserverd2 : 2;
        } bits;
        uint8_t value;
    };

    TextMessageDispatch();
    TextMessageDispatch(Flag flag, std::string text);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TextMessageDispatch& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    Flag flag() const;
    void setFlag(const Flag& newFlag);

    std::string text() const;
    void setText(const std::string& newText);

private:
    Flag m_flag = {0};
    std::string m_text;
};

}
#endif // TEXTMESSAGEDISPATCH_H
