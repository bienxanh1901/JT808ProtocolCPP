#ifndef BCD_H
#define BCD_H

#include "JT808/Common.h"
#include <cstdint>
#include <string>

namespace JT808::BCD {
uint8_t fromHex(const uint8_t& src);
ByteArray fromString(const std::string& src);
uint8_t toHex(const uint8_t& src);
std::string toString(const ByteArray& src);
std::string toString(const uint8_t* data, int size);

}

#endif // BCD_H
