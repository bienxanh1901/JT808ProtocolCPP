#include "JT808/MessageBody/TextMessageDispatch.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/TextMessageDispatchSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>

namespace JT808::MessageBody {

TextMessageDispatch::TextMessageDispatch()
    : MessageBodyBase(Schema::TextMessageDispatchSchema)
{
}

TextMessageDispatch::TextMessageDispatch(Flag flag, std::string text)
    : MessageBodyBase(Schema::TextMessageDispatchSchema)
    , m_flag(flag)
    , m_text(std::move(text))
{
}

void TextMessageDispatch::parse(const ByteArray& data)
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

ByteArray TextMessageDispatch::package()
{
    ByteArray result;
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

void TextMessageDispatch::fromJson(const Json& data)
{
    if (validate(data)) {
        m_flag.value = data["flag"];
        m_text = data["text"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json TextMessageDispatch::toJson()
{
    return {{"flag", m_flag.value}, {"text", m_text}};
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
