
#include "JT808/Message.h"
#include "JT808/MessageIds.h"
#include <JT808/MessageBody/GeneralResponse.h>
#include <gtest/gtest.h>

namespace JT808 {
class MessageTest : public testing::Test
{
protected:
    std::vector<uint8_t> m_rawData {0x7e, 0x80, 0x1, 0x0, 0x5,  0x8, 0x41, 0x23, 0x45, 0x67,
                                    0x89, 0x0,  0x1, 0x0, 0x7b, 0x1, 0xc8, 0x0,  0xf6, 0x7e};
};

TEST_F(MessageTest, TestParseSuccess)
{
    Message message;
    message.parse(m_rawData);
    EXPECT_TRUE(message.isValid());

    Message::Header header(message.header());
    EXPECT_EQ(header.msgID, MessageIds::PlatformGeneralResponseMsgId);
    EXPECT_EQ(header.bodyProps.bits.len, 5);
    EXPECT_EQ(header.bodyProps.bits.encrypt, 0);
    EXPECT_EQ(header.bodyProps.bits.segment, 0);
    EXPECT_EQ(header.phone, "84123456789");
    EXPECT_EQ(header.msgSN, 1);
    EXPECT_EQ(header.pkgEncap.rawData, 0);

    MessageBody::GeneralResponse* body = dynamic_cast<MessageBody::GeneralResponse*>(message.body());
    EXPECT_EQ(body->seq(), 123);
    EXPECT_EQ(body->id(), 456);
    EXPECT_EQ(body->result(), MessageBody::GeneralResponse::Succeeded);
}

TEST_F(MessageTest, TestPackage)
{
    Message::Header header {.msgID = MessageIds::PlatformGeneralResponseMsgId,
                            .bodyProps = {.bits {.len = 5, .encrypt = 0, .segment = 0, .reserve = 0}},
                            .phone = "84123456789",
                            .msgSN = 1,
                            .pkgEncap {.rawData = 0}};

    std::unique_ptr<MessageBody::GeneralResponse> body =
        std::make_unique<MessageBody::GeneralResponse>(123, 456, MessageBody::GeneralResponse::Succeeded);

    Message message(header, std::move(body));

    std::vector<uint8_t> data(message.package());

    EXPECT_EQ(data.size(), m_rawData.size());
    EXPECT_EQ(data, m_rawData);
}

}
