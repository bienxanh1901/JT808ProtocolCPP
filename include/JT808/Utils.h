#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

namespace JT808 {
namespace Utils {

typedef union {
    uint32_t value;
    uint8_t array[4];
} U32Array;

typedef union {
    uint16_t value;
    uint8_t array[2];
} U16Array;

uint16_t endianSwap16(const uint16_t& val);

uint16_t endianSwap16(const std::vector<uint8_t>& data);

uint16_t endianSwap16(uint8_t* data);

uint32_t endianSwap32(const uint32_t& val);

uint32_t endianSwap32(const std::vector<uint8_t>& data);

uint32_t endianSwap32(uint8_t* data);

std::string gbkEncode(const std::string& data);

std::string gbkDecode(const std::string& data);

void printHexArray(const std::vector<uint8_t>& data, std::ostream& out);
void printHexArray(const uint8_t* data, int size, std::ostream& out);
}
}
#endif // UTILS_H
