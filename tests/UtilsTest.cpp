#include <JT808/Utils.h>
#include <cstdint>
#include <gtest/gtest.h>
#include <string>

namespace {
JT808::Utils::U16Array input16 {.value = 0x1234};
JT808::Utils::U32Array input32 {.value = 0x12345678};

uint16_t expectedOutput16 {0x3412};
uint32_t expectedOutput32 {0x78563412};

ByteArray unescapedData {0x30, 0x7e, 0x08, 0x7d, 0x55};
ByteArray escapedData {0x30, 0x7d, 0x02, 0x08, 0x7d, 0x01, 0x55};
uint8_t trueChecksum = 110;
}

namespace JT808::Utils {

TEST(UtilsTest, endianSwap16_1)
{
    uint16_t output = endianSwap16(input16.value);

    EXPECT_EQ(output, expectedOutput16);

    output = endianSwap16(output);

    EXPECT_EQ(output, input16.value);
}

TEST(UtilsTest, endianSwap16_2)
{

    ByteArray const input16Vector(input16.array, input16.array + 2);

    uint16_t const output = endianSwap16(input16Vector);

    EXPECT_EQ(output, expectedOutput16);
}

TEST(UtilsTest, endianSwap16_3)
{
    uint16_t const output = endianSwap16(input16.array);

    EXPECT_EQ(output, expectedOutput16);
}

TEST(UtilsTest, endianSwap32_1)
{
    uint32_t output = endianSwap32(input32.value);

    EXPECT_EQ(output, expectedOutput32);

    output = endianSwap32(output);

    EXPECT_EQ(output, input32.value);
}

TEST(UtilsTest, endianSwap32_2)
{

    ByteArray const input32Vector(input32.array, input32.array + 4);

    uint32_t const output = endianSwap32(input32Vector);

    EXPECT_EQ(output, expectedOutput32);
}

TEST(UtilsTest, endianSwap32_3)
{
    uint32_t const output = endianSwap32(input32.array);

    EXPECT_EQ(output, expectedOutput32);
}

TEST(UtilsTest, gbkEncodeDecode)
{
    // std::string const input("你好");
    // std::string const expectedOutput("\xC4\xE3\xBA\xC3");

    std::string const input("粤B12345");
    std::string const expectedOutput("\xD4\xC1\x42\x31\x32\x33\x34\x35");

    std::string output = gbkEncode(input);
    EXPECT_STREQ(output.c_str(), expectedOutput.c_str());

    output.clear();
    output = gbkDecode(expectedOutput);

    EXPECT_STREQ(output.c_str(), input.c_str());
}

TEST(UtilsTest, gbkDecode2)
{
    std::string const input("粤B12345");
    uint8_t const expectedOutput[8] = {0xD4, 0xC1, 0x42, 0x31, 0x32, 0x33, 0x34, 0x35};

    std::string const output = gbkDecode(expectedOutput, sizeof(expectedOutput));

    EXPECT_STREQ(output.c_str(), input.c_str());
}

TEST(UtilsTest, escape)
{
    ByteArray const data = escape(unescapedData);
    EXPECT_EQ(data.size(), escapedData.size());
    EXPECT_EQ(data, escapedData);
}

TEST(UtilsTest, reverseEscape)
{
    ByteArray const data = reverseEscape(escapedData);
    EXPECT_EQ(data.size(), unescapedData.size());
    EXPECT_EQ(data, unescapedData);
}

TEST(UtilsTest, calculateChecksum)
{
    int const checksum = calculateChecksum(unescapedData);
    EXPECT_EQ(checksum, trueChecksum);
}
}
