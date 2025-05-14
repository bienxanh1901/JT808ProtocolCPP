
#include "JT808/Message.h"
#include <gtest/gtest.h>

namespace JT808 {
class MessageTest : public testing::Test
{
protected:
    ~MessageTest() override { }

    void SetUp() override { }

    void TearDown() override { }

    void TestPackage() { }

    std::vector<uint8_t> m_rawData = {};
    Message m_message;
};

TEST_F(MessageTest, TestConstructor1)
{
    std::vector<uint8_t> data({0x0a, 0x02, 0x35, 0x69, 0x77});
    Message message(data);

    EXPECT_EQ(message.rawData().size(), data.size());

    EXPECT_EQ(message.rawData(), data);
}

TEST_F(MessageTest, TestParseSuccess)
{
    Message message(m_rawData);
    message.parse();

    EXPECT_TRUE(message.isValid());
}

TEST_F(MessageTest, TestPackage)
{
    TestPackage();
}

}
