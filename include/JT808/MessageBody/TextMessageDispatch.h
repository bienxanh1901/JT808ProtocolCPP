#ifndef TEXTMESSAGEDISPATCH_H
#define TEXTMESSAGEDISPATCH_H

#include "MessageBodyBase.h"

#include <cstdint>
#include <vector>

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
            uint8_t : 1;
            uint8_t reserverd2 : 2;
        } bits;
        uint8_t value;
    };

    TextMessageDispatch() = default;
    TextMessageDispatch(Flag flag, const std::string& text);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TextMessageDispatch& other);

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
