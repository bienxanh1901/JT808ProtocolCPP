#include "JT808/MessageBody/RSAPublicKey.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

RSAPublicKey::RSAPublicKey(const std::vector<uint8_t>& data)
    : m_data(data)
{
}

void RSAPublicKey::parse(const std::vector<uint8_t>& data)
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

std::vector<uint8_t> RSAPublicKey::package()
{
    std::vector<uint8_t> result;
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

std::vector<uint8_t> RSAPublicKey::data() const
{
    return m_data;
}

void RSAPublicKey::setData(const std::vector<uint8_t>& newData)
{
    m_data = newData;
}

}
