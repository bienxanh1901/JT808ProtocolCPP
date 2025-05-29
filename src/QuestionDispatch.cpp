#include "JT808/MessageBody/QuestionDispatch.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/QuestionDispatchSchema.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

QuestionDispatch::QuestionDispatch()
    : MessageBodyBase(Schema::QuestionDispatchSchema)
{
}

QuestionDispatch::QuestionDispatch(Flag flag, std::string question, const std::vector<Answer>& answers)
    : MessageBodyBase(Schema::QuestionDispatchSchema)
    , m_flag(flag)
    , m_question(std::move(question))
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
    // m_answers
    for (auto& item : m_answers) {
        Utils::append(item.package(), result);
    }

    return result;
}

bool QuestionDispatch::operator==(const QuestionDispatch& other) const
{
    return m_flag.value == other.m_flag.value && m_question == other.m_question && m_answers == other.m_answers;
}

void QuestionDispatch::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        Answer item = {0};

        m_flag.value = data["flag"];
        m_question = data["question"];

        for (auto& answer : data["answers"]) {
            item.fromJson(answer);
            m_answers.push_back(item);
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json QuestionDispatch::toJson()
{
    nlohmann::json result(nlohmann::json::object(
        {{"flag", m_flag.value}, {"question", m_question}, {"length", m_answers.size()}, {"answers", {}}}));
    for (auto& item : m_answers) {
        result["answers"].push_back(item.toJson());
    }

    return result;
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

int QuestionDispatch::Answer::parse(const uint8_t* data, int /*size*/)
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

std::vector<uint8_t> QuestionDispatch::Answer::package() const
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

void QuestionDispatch::Answer::fromJson(const nlohmann::json& data)
{
    id = data["id"];
    content = data["answer"];
}

nlohmann::json QuestionDispatch::Answer::toJson()
{
    return {{"id", id}, {"answer", content}};
}

}
