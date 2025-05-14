#include <gtest/gtest.h>

#include "JT808/MessageBody/MessageBodyBase.h"
#include "MessageBodyBaseTest.h"

namespace JT808 {
namespace MessageBody {

class BodyBaseTest : public MessageBodyBaseTest<MessageBodyBase>
{
};

TEST_F(BodyBaseTest, TestConstructor1)
{
    std::vector<uint8_t> data({0x0a, 0x02, 0x35, 0x69, 0x77});
    MessageBodyBase body(data);

    EXPECT_EQ(body.rawData().size(), data.size());

    EXPECT_EQ(body.rawData(), data);
}

TEST_F(BodyBaseTest, TestConstructor2)
{
    uint8_t data[] = {0x0a, 0x02, 0x35, 0x69, 0x77};
    MessageBodyBase body(data, 5);

    EXPECT_EQ(body.rawData().size(), 5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(body.rawData()[i], data[i]);
    }
}

}
}
