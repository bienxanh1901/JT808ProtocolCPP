
#include "JT808/Message.h"
#include "JT808/MessageIds.h"
#include <JT808/MessageBody/GeneralResponse.h>
#include <gtest/gtest.h>
#include <memory>
#include <utility>

namespace JT808 {
class MessageTest : public testing::Test
{
protected:
    ByteArray m_rawData {0x7e, 0x80, 0x1, 0x0, 0x5,  0x8, 0x41, 0x23, 0x45, 0x67,
                         0x89, 0x0,  0x1, 0x0, 0x7b, 0x1, 0xc8, 0x0,  0xf6, 0x7e};
    Json m_object = Json::object(
        {{"header",
          Json::object({{"id", MessageIds::PlatformGeneralResponseMsgId},
                        {"encrypt", 0},
                        {"length", 5},
                        {"phone", "84123456789"},
                        {"seq", 1},
                        {"segment", 0}})},
         {"body", Json::object({{"seq", 123}, {"id", 456}, {"result", MessageBody::GeneralResponse::Succeeded}})}});
};

TEST_F(MessageTest, TestParseSuccess)
{
    Message message;
    message.parse(m_rawData);
    EXPECT_TRUE(message.isValid());

    Message::Header const header(message.header());
    EXPECT_EQ(header.id, MessageIds::PlatformGeneralResponseMsgId);
    EXPECT_EQ(header.bodyProps.bits.len, 5);
    EXPECT_EQ(header.bodyProps.bits.encrypt, 0);
    EXPECT_EQ(header.bodyProps.bits.segment, 0);
    EXPECT_EQ(header.phone, "84123456789");
    EXPECT_EQ(header.seq, 1);
    EXPECT_EQ(header.pkgEncap.rawData, 0);

    auto* body = dynamic_cast<MessageBody::GeneralResponse*>(message.body());
    EXPECT_EQ(body->seq(), 123);
    EXPECT_EQ(body->id(), 456);
    EXPECT_EQ(body->result(), MessageBody::GeneralResponse::Succeeded);
}

TEST_F(MessageTest, TestPackage)
{
    Message::Header const header {.id = MessageIds::PlatformGeneralResponseMsgId,
                                  .bodyProps = {.bits {.len = 5, .encrypt = 0, .segment = 0, .reserve = 0}},
                                  .phone = "84123456789",
                                  .seq = 1,
                                  .pkgEncap {.rawData = 0}};

    std::unique_ptr<MessageBody::GeneralResponse> body =
        std::make_unique<MessageBody::GeneralResponse>(123, 456, MessageBody::GeneralResponse::Succeeded);

    Message message(header, std::move(body));

    ByteArray const data(message.package());

    EXPECT_EQ(data.size(), m_rawData.size());
    EXPECT_EQ(data, m_rawData);
}

TEST_F(MessageTest, TestFromJsom)
{
    Message message;
    message.fromJson(m_object);
    EXPECT_TRUE(message.isValid());

    Message::Header const header(message.header());
    EXPECT_EQ(header.id, MessageIds::PlatformGeneralResponseMsgId);
    EXPECT_EQ(header.bodyProps.bits.len, 5);
    EXPECT_EQ(header.bodyProps.bits.encrypt, 0);
    EXPECT_EQ(header.bodyProps.bits.segment, 0);
    EXPECT_EQ(header.phone, "84123456789");
    EXPECT_EQ(header.seq, 1);
    EXPECT_EQ(header.pkgEncap.rawData, 0);

    auto* body = dynamic_cast<MessageBody::GeneralResponse*>(message.body());
    EXPECT_EQ(body->seq(), 123);
    EXPECT_EQ(body->id(), 456);
    EXPECT_EQ(body->result(), MessageBody::GeneralResponse::Succeeded);
}

TEST_F(MessageTest, TestToJson)
{
    Message message;
    message.parse(m_rawData);

    Json object = message.toJson();
    EXPECT_EQ(m_object, object);
}

}
