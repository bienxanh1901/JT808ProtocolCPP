#ifndef UTILS_H
#define UTILS_H

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
uint16_t endianSwap16(const std::vector<uint8_t>& data);
uint16_t endianSwap16(const uint8_t* data);
uint32_t endianSwap32(const uint32_t& val);
uint32_t endianSwap32(const std::vector<uint8_t>& data);
uint32_t endianSwap32(const uint8_t* data);
std::string gbkEncode(const std::string& data);
std::string gbkDecode(const std::string& data);
std::string gbkDecode(const uint8_t* data, int size);
void printHexArray(const std::vector<uint8_t>& data, std::ostream& out);
void printHexArray(const uint8_t* data, int size, std::ostream& out);
std::vector<uint8_t> escape(const std::vector<uint8_t>& data);
std::vector<uint8_t> reverseEscape(const std::vector<uint8_t>& data);
uint8_t calculateChecksum(const uint8_t* data, int len);
uint8_t calculateChecksum(const std::vector<uint8_t>& data);
void appendU16(uint16_t val, std::vector<uint8_t>& data);
void appendU32(uint32_t val, std::vector<uint8_t>& data);
void appendBCD(const std::string& val, std::vector<uint8_t>& data);
void appendGBK(const std::string& val, std::vector<uint8_t>& data);
void appendNull(std::vector<uint8_t>& data, int length);
void append(const std::string& val, std::vector<uint8_t>& data);
void append(const std::vector<uint8_t>& val, std::vector<uint8_t>& data);
void append(const std::vector<uint16_t>& val, std::vector<uint8_t>& data);
void append(const std::vector<uint32_t>& val, std::vector<uint8_t>& data);
void append(const uint8_t* val, int size, std::vector<uint8_t>& data);
void eraseTrailingNull(std::string& data);

}
#endif // UTILS_H
