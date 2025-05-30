#include "JT808/Utils.h"
#include "JT808/BCD.h"
#include <cstring>
#include <iconv.h>

namespace JT808::Utils {

/**
 * @brief EndianSwap16
 * @param val
 * @return
 */
uint16_t endianSwap16(const uint16_t& val)
{
    return (val >> 8) | (val << 8);
}

/**
 * @brief EndianSwap16
 * @param data
 * @return
 */
uint16_t endianSwap16(const std::vector<uint8_t>& data)
{
    U16Array tmp = {.array = {data[0], data[1]}};

    return endianSwap16(tmp.value);
}

/**
 * @brief EndianSwap16
 * @param data
 * @return
 */
uint16_t endianSwap16(const uint8_t* data)
{
    U16Array tmp = {.array = {data[0], data[1]}};

    return endianSwap16(tmp.value);
}

/**
 * @brief EndianSwap32
 * @param val
 * @return
 */
uint32_t endianSwap32(const uint32_t& val)
{
    return ((val >> 24) & 0xff) | ((val >> 8) & 0xff00) | ((val << 8) & 0xff0000) | ((val << 24) & 0xff000000);
}

/**
 * @brief endianSwap32
 * @param data
 * @return
 */
uint32_t endianSwap32(const std::vector<uint8_t>& data)
{
    U32Array tmp = {.array = {data[0], data[1], data[2], data[3]}};

    return endianSwap32(tmp.value);
}

/**
 * @brief endianSwap32
 * @param data
 * @return
 */
uint32_t endianSwap32(const uint8_t* data)
{
    U32Array tmp = {.array = {data[0], data[1], data[2], data[3]}};

    return endianSwap32(tmp.value);
}

/**
 * @brief gbkEncode
 * @param data
 * @return
 */
std::string gbkEncode(const std::string& data)
{
    std::string result("");
    iconv_t encoder = iconv_open("GBK", "UTF-8");

    if (encoder == (iconv_t)-1) {
        return result;
    }

    size_t inBytesLeft = data.size();
    size_t outBytesLeft = 2 * data.size() + 1;
    std::vector<char> gbkBuffer(outBytesLeft);
    char* inPtr = const_cast<char*>(data.data());
    char* outPtr = gbkBuffer.data();

    if (iconv(encoder, &inPtr, &inBytesLeft, &outPtr, &outBytesLeft) != -1) {
        *outPtr = '\0';
        result.assign(gbkBuffer.data(), gbkBuffer.size());
    }

    iconv_close(encoder);
    return result;
}

/**
 * @brief gbkDecode
 * @param data
 * @return
 */
std::string gbkDecode(const std::string& data)
{
    std::string result("");
    iconv_t decoder = iconv_open("UTF-8", "GBK");

    if (decoder == (iconv_t)-1) {
        return result;
    }

    size_t inBytesLeft = data.size();
    size_t outBytesLeft = data.size() * 4;
    std::vector<char> utf8Buffer(outBytesLeft + 1);
    char* inPtr = const_cast<char*>(data.data());
    char* outPtr = utf8Buffer.data();

    if (iconv(decoder, &inPtr, &inBytesLeft, &outPtr, &outBytesLeft) != -1) {
        *outPtr = '\0';
        result.assign(utf8Buffer.data(), utf8Buffer.size());
    }

    iconv_close(decoder);
    return result;
}

void printHexArray(const uint8_t* data, int size, std::ostream& out)
{
    out << "[";
    out << "0x" << std::hex << (int)data[0];
    for (int i = 1; i < size; i++) {
        out << ", ";
        out << "0x" << std::hex << (int)data[i];
    }

    out << "]";
}

void printHexArray(const std::vector<uint8_t>& data, std::ostream& out)
{
    printHexArray(data.data(), data.size(), out);
}

std::vector<uint8_t> escape(const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> result;

    for (auto& val : data) {
        if (val == ProtocolSign) {
            result.push_back(ProtocolEscape);
            result.push_back(ProtocolEscapeSign);
        } else if (val == ProtocolEscape) {
            result.push_back(ProtocolEscape);
            result.push_back(ProtocolEscapeEscape);
        } else {
            result.push_back(val);
        }
    }

    return result;
}

std::vector<uint8_t> reverseEscape(const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> result;

    for (int i = 0; i < data.size(); i++) {
        if (data[i] == ProtocolEscape && data[i + 1] == ProtocolEscapeSign) {
            result.push_back(ProtocolSign);
            ++i;
        } else if (data[i] == ProtocolEscape && data[i + 1] == ProtocolEscapeEscape) {
            result.push_back(ProtocolEscape);
            ++i;
        } else {
            result.push_back(data[i]);
        }
    }

    return result;
}

uint8_t calculateChecksum(const uint8_t* data, int len)
{
    uint8_t checksum = 0;

    for (int i = 0; i < len; i++) {
        checksum = checksum ^ data[i];
    }

    return checksum;
}

uint8_t calculateChecksum(const std::vector<uint8_t>& data)
{
    return calculateChecksum(data.data(), data.size());
}

void appendU16(uint16_t val, std::vector<uint8_t>& data)
{
    U16Array m_u16Array {.value = Utils::endianSwap16(val)};
    data.insert(data.end(), m_u16Array.array, m_u16Array.array + sizeof(m_u16Array));
}

void appendU32(uint32_t val, std::vector<uint8_t>& data)
{
    U32Array m_u32Array {.value = Utils::endianSwap16(val)};
    m_u32Array.value = Utils::endianSwap32(val);
    data.insert(data.end(), m_u32Array.array, m_u32Array.array + sizeof(m_u32Array));
}

void appendBCD(const std::string val, std::vector<uint8_t>& data)
{
    std::vector<uint8_t> bcd = BCD::fromString(val);
    data.insert(data.end(), bcd.begin(), bcd.end());
}

}
