#ifndef BCD_H
#define BCD_H

#include <cstdint>
#include <string>
#include <vector>

namespace JT808::BCD {
uint8_t fromHex(const uint8_t& src);
std::vector<uint8_t> fromString(const std::string& src);
uint8_t toHex(const uint8_t& src);
std::string toString(const std::vector<uint8_t>& src);

}

#endif // BCD_H
