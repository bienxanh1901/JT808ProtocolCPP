#include "JT808/MessageBody/RSAPublicKey.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/RSAPublicKeySchema.h"
#include "JT808/Utils.h"
#include <cstdint>

namespace JT808::MessageBody {

RSAPublicKey::RSAPublicKey()
    : MessageBodyBase(Schema::RSAPublicKeySchema)
{
}

RSAPublicKey::RSAPublicKey(const ByteArray& data)
    : MessageBodyBase(Schema::RSAPublicKeySchema)
    , m_data(data)
{
}

void RSAPublicKey::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void RSAPublicKey::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;

    // length
    uint32_t const length = Utils::endianSwap32(data);
    pos += sizeof(length);
    // data
    m_data.assign(data + pos, data + pos + length);

    setIsValid(true);
}

ByteArray RSAPublicKey::package()
{
    ByteArray result;
    // length
    Utils::appendU32(m_data.size(), result);
    // data
    Utils::append(m_data, result);

    return result;
}

bool RSAPublicKey::operator==(const RSAPublicKey& other) const
{
    return m_data == other.m_data;
}

void RSAPublicKey::fromJson(const Json& data)
{
    if (validate(data)) {
        m_data = data["data"].get<ByteArray>();
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json RSAPublicKey::toJson()
{
    return {{"data", m_data}};
}

ByteArray RSAPublicKey::data() const
{
    return m_data;
}

void RSAPublicKey::setData(const ByteArray& newData)
{
    m_data = newData;
}

}
