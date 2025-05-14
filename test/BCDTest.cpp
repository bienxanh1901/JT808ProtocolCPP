#include "JT808/BCD.h"
#include "JT808/Utils.h"
#include <gtest/gtest.h>

namespace JT808 {
namespace BCD {

uint8_t inputHex = 70;
std::string inputString = "8700101000000";
uint8_t expectedOutputHex = 0x70;
std::vector<uint8_t> expectedOutputVector = {0x08, 0x70, 0x01, 0x01, 0x00, 0x00, 0x00};

TEST(BCDTest, fromHex)
{
    uint8_t output = fromHex(inputHex);

    EXPECT_EQ(output, expectedOutputHex);
}

TEST(BCDTest, fromString)
{
    std::vector<uint8_t> output = fromString(inputString);
    EXPECT_EQ(output, expectedOutputVector);
}

TEST(BCDTest, toHex)
{
    uint8_t output = toHex(expectedOutputHex);

    EXPECT_EQ(output, inputHex);
}

TEST(BCDTest, toString)
{
    std::string output = toString(expectedOutputVector);
    EXPECT_EQ(output, inputString);
}
}
}
