#include "JT808/BCD.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace {
uint8_t inputHex(70);
std::string inputString("8700101000000");
uint8_t expectedOutputHex(0x70);
std::vector<uint8_t> expectedOutputVector {0x08, 0x70, 0x01, 0x01, 0x00, 0x00, 0x00};
}

namespace JT808::BCD {

TEST(BCDTest, fromHex)
{
    uint8_t const output = fromHex(inputHex);

    EXPECT_EQ(output, expectedOutputHex);
}

TEST(BCDTest, fromString)
{
    std::vector<uint8_t> const output = fromString(inputString);
    EXPECT_EQ(output, expectedOutputVector);
}

TEST(BCDTest, toHex)
{
    uint8_t const output = toHex(expectedOutputHex);

    EXPECT_EQ(output, inputHex);
}

TEST(BCDTest, toString)
{
    std::string const output = toString(expectedOutputVector);
    EXPECT_EQ(output, inputString);
}
}
