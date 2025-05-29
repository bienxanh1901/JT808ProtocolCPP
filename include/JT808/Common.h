#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
namespace JT808 {

enum DataType : uint8_t
{
    BYTE = 0,
    WORD,
    DWORD,
    BYTEARRAY,
    BCD,
    STRING,
};

}
#endif // COMMON_H
