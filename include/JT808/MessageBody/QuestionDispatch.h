#ifndef QUESTIONDISPATCH_H
#define QUESTIONDISPATCH_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class QuestionDispatch : public MessageBodyBase
{
public:
    union Flag {
        struct
        {
            uint8_t sos : 1;
            uint8_t reserved : 2;
            uint8_t terminalTTS : 1;
            uint8_t advDisplay : 1;
            uint8_t reserverd2 : 3;
        } bits;
        uint8_t value;
    };

    struct Answer
    {
        uint8_t id;
        uint16_t length;
        std::string content;

        bool operator==(const Answer& other)
        {
            return id == other.id && length == other.length && content == other.content;
        }
    };

    QuestionDispatch() = default;
    QuestionDispatch(Flag flag, const std::string& question, const std::vector<Answer>& answers);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const QuestionDispatch& other);

    Flag flag() const;
    void setFlag(const Flag& newFlag);
    uint8_t length() const;
    void setLength(uint8_t newLength);
    std::string question() const;
    void setQuestion(const std::string& newQuestion);

    std::vector<Answer> answers() const;
    void setAnswers(const std::vector<Answer>& newAnswers);

private:
    Flag m_flag = {0};
    uint8_t m_length = 0;
    std::string m_question;
    std::vector<Answer> m_answers;
};

}
#endif // QUESTIONDISPATCH_H
