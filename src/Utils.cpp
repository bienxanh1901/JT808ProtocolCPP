#include "JT808/Utils.h"
#include "JT808/BCD.h"
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iconv.h>
#include <ios>
#include <ostream>
#include <string>
#include <vector>

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
uint16_t endianSwap16(const ByteArray& data)
{
    U16Array const tmp = {.array = {data[0], data[1]}};

    return endianSwap16(tmp.value);
}

/**
 * @brief EndianSwap16
 * @param data
 * @return
 */
uint16_t endianSwap16(const uint8_t* data)
{
    U16Array const tmp = {.array = {data[0], data[1]}};

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
uint32_t endianSwap32(const ByteArray& data)
{
    U32Array const tmp = {.array = {data[0], data[1], data[2], data[3]}};

    return endianSwap32(tmp.value);
}

/**
 * @brief endianSwap32
 * @param data
 * @return
 */
uint32_t endianSwap32(const uint8_t* data)
{
    U32Array const tmp = {.array = {data[0], data[1], data[2], data[3]}};

    return endianSwap32(tmp.value);
}

/**
 * @brief gbkEncode
 * @param data
 * @return
 */
std::string gbkEncode(const std::string& data)
{
    std::string result;
    iconv_t encoder = iconv_open("GBK", "UTF-8");

    if (encoder == (iconv_t)-1) {
        return result;
    }

    size_t inBytesLeft = data.size();
    size_t outBytesLeft = (2 * data.size()) + 1;
    std::vector<char> gbkBuffer(outBytesLeft);
    char* inPtr = const_cast<char*>(data.data());
    char* outPtr = gbkBuffer.data();

    if (iconv(encoder, &inPtr, &inBytesLeft, &outPtr, &outBytesLeft) != -1) {
        *outPtr = '\0';
        result.assign(gbkBuffer.data(), gbkBuffer.size());
        eraseTrailingNull(result);
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
    std::string result;
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
        eraseTrailingNull(result);
    }

    iconv_close(decoder);
    return result;
}

std::string gbkDecode(const uint8_t* data, int size)
{
    std::string const tmp(data, data + size);

    return gbkDecode(tmp);
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

void printHexArray(const ByteArray& data, std::ostream& out)
{
    printHexArray(data.data(), data.size(), out);
}

ByteArray escape(const ByteArray& data)
{
    ByteArray result;

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

ByteArray reverseEscape(const ByteArray& data)
{
    ByteArray result;

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

uint8_t calculateChecksum(const ByteArray& data)
{
    return calculateChecksum(data.data(), data.size());
}

void appendU16(uint16_t val, ByteArray& data)
{
    U16Array u16Array {.value = Utils::endianSwap16(val)};
    append(u16Array.array, 2, data);
}

void appendU32(uint32_t val, ByteArray& data)
{
    U32Array u32Array {.value = Utils::endianSwap32(val)};
    append(u32Array.array, 4, data);
}

void appendBCD(const std::string& val, ByteArray& data)
{
    append(BCD::fromString(val), data);
}

void appendGBK(const std::string& val, ByteArray& data)
{
    append(gbkEncode(val), data);
}

void appendNull(ByteArray& data, int length)
{
    Utils::append(ByteArray(length, 0x00), data);
}

void append(const std::string& val, ByteArray& data)
{
    data.insert(data.end(), val.begin(), val.end());
}

void append(const ByteArray& val, ByteArray& data)
{
    data.insert(data.end(), val.begin(), val.end());
}

void append(const uint8_t* val, int size, ByteArray& data)
{
    data.insert(data.end(), val, val + size);
}

void append(const std::vector<uint16_t>& val, ByteArray& data)
{
    for (const auto& item : val) {
        appendU16(item, data);
    }
}

void append(const std::vector<uint32_t>& val, ByteArray& data)
{
    for (const auto& item : val) {
        appendU32(item, data);
    }
}

void eraseTrailingNull(std::string& data)
{
    data.erase(std::remove(data.begin(), data.end(), 0x00), data.end());
}

}
