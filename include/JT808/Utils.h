#ifndef UTILS_H
#define UTILS_H

#include "JT808/Common.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace JT808::Utils {

/**
 * @brief ProtocolEscapeFlags
 */
enum ProtocolEscapeFlags : uint8_t
{
    ProtocolSign = 0x7E,
    ProtocolEscape = 0x7D,
    ProtocolEscapeSign = 0x02,
    ProtocolEscapeEscape = 0x01,
};

union U64Array {
    uint64_t value = 0;
    uint8_t array[8];
};

union U32Array {
    uint32_t value = 0;
    uint8_t array[4];
};

union U16Array {
    uint16_t value = 0;
    uint8_t array[2];
};

uint16_t endianSwap16(const uint16_t& val);
uint16_t endianSwap16(const ByteArray& data);
uint16_t endianSwap16(const uint8_t* data);
uint32_t endianSwap32(const uint32_t& val);
uint32_t endianSwap32(const ByteArray& data);
uint32_t endianSwap32(const uint8_t* data);
std::string gbkEncode(const std::string& data);
std::string gbkDecode(const std::string& data);
std::string gbkDecode(const uint8_t* data, int size);
void printHexArray(const ByteArray& data, std::ostream& out);
void printHexArray(const uint8_t* data, int size, std::ostream& out);
ByteArray escape(const ByteArray& data);
ByteArray reverseEscape(const ByteArray& data);
uint8_t calculateChecksum(const uint8_t* data, int len);
uint8_t calculateChecksum(const ByteArray& data);
void appendU16(uint16_t val, ByteArray& data);
void appendU32(uint32_t val, ByteArray& data);
void appendBCD(const std::string& val, ByteArray& data);
void appendGBK(const std::string& val, ByteArray& data);
void appendNull(ByteArray& data, int length);
void append(const std::string& val, ByteArray& data);
void append(const ByteArray& val, ByteArray& data);
void append(const std::vector<uint16_t>& val, ByteArray& data);
void append(const std::vector<uint32_t>& val, ByteArray& data);
void append(const uint8_t* val, int size, ByteArray& data);
void eraseTrailingNull(std::string& data);

}
#endif // UTILS_H
