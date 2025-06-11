#ifndef QUESTIONDISPATCH_H
#define QUESTIONDISPATCH_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <string>
#include <vector>

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
        uint8_t value = 0;
    };

    struct Answer
    {
        uint8_t id = 0;
        std::string content;

        bool operator==(const Answer& other) const;
        int parse(const uint8_t* data, int size);
        ByteArray package() const;

        void fromJson(const Json& data);
        Json toJson();
    };

    QuestionDispatch();
    QuestionDispatch(Flag flag, std::string question, const std::vector<Answer>& answers);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const QuestionDispatch& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    Flag flag() const;
    void setFlag(const Flag& newFlag);
    std::string question() const;
    void setQuestion(const std::string& newQuestion);

    std::vector<Answer> answers() const;
    void setAnswers(const std::vector<Answer>& newAnswers);

private:
    Flag m_flag = {0};
    std::string m_question;
    std::vector<Answer> m_answers;
};

}
#endif // QUESTIONDISPATCH_H
