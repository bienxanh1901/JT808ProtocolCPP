#ifndef COMMON_H
#define COMMON_H

#include "nlohmann/json-schema.hpp"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

using JsonValidator = nlohmann::json_schema::json_validator;
using Json = nlohmann::json;
using ByteArray = std::vector<uint8_t>;

namespace JT808 {

enum DataType : uint8_t
{
    BYTE = 0,
    WORD,
    DWORD,
    BYTEARRAY,
    BCDUtils,
    STRING,
};
}
#endif // COMMON_H
