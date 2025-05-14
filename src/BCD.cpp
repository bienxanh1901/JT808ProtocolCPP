#include "JT808/BCD.h"

namespace JT808 {
namespace BCD {

uint8_t charTodigit(const char& digit)
{
    return digit - '0';
}

char digitToChar(uint8_t digit)
{
    return digit + '0';
}

uint8_t fromHex(const uint8_t& src)
{
    return ((src / 10) << 4) + (src % 10);
}

std::vector<uint8_t> fromString(const std::string& src)
{
    std::vector<uint8_t> result;
    size_t pos = 0;

    if (src.size() % 2 != 0) {
        result.push_back(fromHex(charTodigit(src[pos])));
        ++pos;
    }

    for (; pos < src.size();) {
        result.push_back(fromHex(charTodigit(src[pos]) * 10 + charTodigit(src[pos + 1])));
        pos += 2;
    }

    return result;
}

uint8_t toHex(const uint8_t& src)
{
    return (src >> 4) * 10 + (src & 0x0f);
}

std::string toString(const std::vector<uint8_t>& src)
{
    std::string result("");
    uint8_t tmp = 0;
    for (int i = 0; i < src.size(); i++) {
        tmp = toHex(src[i]);

        if (i == 0 && tmp <= 9) {
            result.push_back(digitToChar(tmp));
        } else {
            result.push_back(digitToChar(tmp / 10));
            result.push_back(digitToChar(tmp % 10));
        }
    }

    return result;
}

}
}
