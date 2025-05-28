#include "JT808/MessageBody/TextMessageDispatch.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

TextMessageDispatch::TextMessageDispatch(Flag flag, std::string text)
    : m_flag(flag)
    , m_text(std::move(text))
{
}

void TextMessageDispatch::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TextMessageDispatch::parse(const uint8_t* data, int size)
{
    int pos = 0;
    // flag
    m_flag.value = data[pos++];
    // information
    m_text = Utils::gbkDecode(data + pos, size - pos);

    setIsValid(true);
}

std::vector<uint8_t> TextMessageDispatch::package()
{
    std::vector<uint8_t> result;
    // flag
    result.push_back(m_flag.value);
    // information
    Utils::appendGBK(m_text, result);

    return result;
}

bool TextMessageDispatch::operator==(const TextMessageDispatch& other) const
{
    return m_flag.value == other.m_flag.value && m_text == other.m_text;
}

TextMessageDispatch::Flag TextMessageDispatch::flag() const
{
    return m_flag;
}

void TextMessageDispatch::setFlag(const Flag& newFlag)
{
    m_flag = newFlag;
}

std::string TextMessageDispatch::text() const
{
    return m_text;
}

void TextMessageDispatch::setText(const std::string& newText)
{
    m_text = newText;
}

}
