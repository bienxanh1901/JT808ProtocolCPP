#include "JT808/MessageBody/QuestionDispatch.h"

namespace JT808::MessageBody {

QuestionDispatch::QuestionDispatch(Flag flag, const std::string& question, const std::vector<Answer>& answers)
    : MessageBodyBase()
    , m_flag(flag)
    , m_length(question.length())
    , m_question(question)
    , m_answers(answers)
{
}

void QuestionDispatch::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void QuestionDispatch::parse(const uint8_t* data, int size)
{
    int pos = 0;
    Answer answer = {0};

    m_flag.value = data[pos++];
    m_length = data[pos++];
    m_question = Utils::gbkDecode(data + pos, m_length);
    pos += m_length;

    while (pos < size - 1) {
        answer.id = data[pos++];
        answer.length = Utils::endianSwap16(data + pos);
        pos += sizeof(answer.length);
        answer.content = Utils::gbkDecode(data + pos, answer.length);
        pos += answer.length;
        m_answers.push_back(answer);
    }

    setIsValid(true);
}

std::vector<uint8_t> QuestionDispatch::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_flag.value);
    result.push_back(m_length);
    Utils::appendGBK(m_question, result);

    for (auto& answer : m_answers) {
        result.push_back(answer.id);
        Utils::appendU16(answer.length, result);
        Utils::appendGBK(answer.content, result);
    }

    return result;
}

bool QuestionDispatch::operator==(const QuestionDispatch& other)
{
    bool result = m_flag.value == other.m_flag.value && m_length == other.m_length && m_question == other.m_question
        && m_answers.size() == other.m_answers.size();

    if (result) {
        for (int i = 0; i < m_answers.size(); i++) {
            if (!(m_answers[i] == other.m_answers[i])) {
                return false;
            }
        }
    }

    return true;
}

QuestionDispatch::Flag QuestionDispatch::flag() const
{
    return m_flag;
}

void QuestionDispatch::setFlag(const Flag& newFlag)
{
    m_flag = newFlag;
}

uint8_t QuestionDispatch::length() const
{
    return m_length;
}

void QuestionDispatch::setLength(uint8_t newLength)
{
    m_length = newLength;
}

std::string QuestionDispatch::question() const
{
    return m_question;
}

void QuestionDispatch::setQuestion(const std::string& newQuestion)
{
    m_question = newQuestion;
}

std::vector<QuestionDispatch::Answer> QuestionDispatch::answers() const
{
    return m_answers;
}

void QuestionDispatch::setAnswers(const std::vector<Answer>& newAnswers)
{
    m_answers = newAnswers;
}

}
