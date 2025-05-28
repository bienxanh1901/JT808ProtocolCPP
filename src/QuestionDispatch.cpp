#include "JT808/MessageBody/QuestionDispatch.h"

namespace JT808::MessageBody {

QuestionDispatch::QuestionDispatch(Flag flag, const std::string& question, const std::vector<Answer>& answers)
    : MessageBodyBase()
    , m_flag(flag)
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
    int pos1 = 0;
    int length = 0;
    // flag
    m_flag.value = data[pos++];
    // length
    length = data[pos++];
    // question
    m_question = Utils::gbkDecode(data + pos, length);
    pos += length;

    // answers
    while (pos < size - 1) {
        Answer item = {0};
        pos1 = item.parse(data + pos, size);
        pos += pos1;
        m_answers.push_back(item);
    }

    setIsValid(true);
}

std::vector<uint8_t> QuestionDispatch::package()
{
    std::vector<uint8_t> result;
    // flag
    result.push_back(m_flag.value);
    // length
    result.push_back(m_question.size());
    // question
    Utils::appendGBK(m_question, result);
    // anwsers
    for (auto& item : m_answers) {
        Utils::append(item.package(), result);
    }

    return result;
}

bool QuestionDispatch::operator==(const QuestionDispatch& other) const
{
    return m_flag.value == other.m_flag.value && m_question == other.m_question && m_answers == other.m_answers;
}

QuestionDispatch::Flag QuestionDispatch::flag() const
{
    return m_flag;
}

void QuestionDispatch::setFlag(const Flag& newFlag)
{
    m_flag = newFlag;
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

bool QuestionDispatch::Answer::operator==(const Answer& other) const
{
    return id == other.id && content == other.content;
}

int QuestionDispatch::Answer::parse(const uint8_t* data, int size)
{
    int pos = 0;
    uint16_t length = 0;
    // id
    id = data[pos++];
    // length
    length = Utils::endianSwap16(data + pos);
    pos += sizeof(length);
    // content
    content = Utils::gbkDecode(data + pos, length);
    pos += length;

    return pos;
}

std::vector<uint8_t> QuestionDispatch::Answer::package()
{
    std::vector<uint8_t> result;
    // id
    result.push_back(id);
    // length
    Utils::appendU16(content.size(), result);
    // content
    Utils::appendGBK(content, result);
    return result;
}

}
