#include <JT808/Utils.h>
#include <gtest/gtest.h>

namespace JT808::Utils {
U16Array input16 {.value = 0x1234};
U32Array input32 {.value = 0x12345678};

uint16_t expectedOutput16 {0x3412};
uint32_t expectedOutput32 {0x78563412};

std::vector<uint8_t> unescapedData {0x30, 0x7e, 0x08, 0x7d, 0x55};
std::vector<uint8_t> escapedData {0x30, 0x7d, 0x02, 0x08, 0x7d, 0x01, 0x55};
uint8_t trueChecksum = 110;

TEST(UtilsTest, endianSwap16_1)
{
    uint16_t output = endianSwap16(input16.value);

    EXPECT_EQ(output, expectedOutput16);

    output = endianSwap16(output);

    EXPECT_EQ(output, input16.value);
}

TEST(UtilsTest, endianSwap16_2)
{

    std::vector<uint8_t> input16Vector(input16.array, input16.array + 2);

    uint16_t output = endianSwap16(input16Vector);

    EXPECT_EQ(output, expectedOutput16);
}

TEST(UtilsTest, endianSwap16_3)
{
    uint16_t output = endianSwap16(input16.array);

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

    std::vector<uint8_t> input32Vector(input32.array, input32.array + 4);

    uint32_t output = endianSwap32(input32Vector);

    EXPECT_EQ(output, expectedOutput32);
}

TEST(UtilsTest, endianSwap32_3)
{
    uint32_t output = endianSwap32(input32.array);

    EXPECT_EQ(output, expectedOutput32);
}

TEST(UtilsTest, gbkEncodeDecode)
{
    std::string input("你好");
    std::string expectedOutput("\xC4\xE3\xBA\xC3");

    std::string output = gbkEncode(input);
    EXPECT_STREQ(output.c_str(), expectedOutput.c_str());

    output.clear();
    output = gbkDecode(expectedOutput);

    EXPECT_STREQ(output.c_str(), input.c_str());
}

TEST(UtilsTest, escape)
{
    std::vector<uint8_t> data = escape(unescapedData);
    EXPECT_EQ(data.size(), escapedData.size());
    EXPECT_EQ(data, escapedData);
}

TEST(UtilsTest, reverseEscape)
{
    std::vector<uint8_t> data = reverseEscape(escapedData);
    EXPECT_EQ(data.size(), unescapedData.size());
    EXPECT_EQ(data, unescapedData);
}

TEST(UtilsTest, calculateChecksum)
{
    int checksum = calculateChecksum(unescapedData);
    EXPECT_EQ(checksum, trueChecksum);
}
}
