
#include "JT808/MessageBody/PhoneBookSetting.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class PhoneBookSettingTest : public MessageBodyBaseTest<PhoneBookSetting>
{
protected:
    void SetUp() override
    {

        std::vector<PhoneBookSetting::ContactItem> const contacts = {{1, "1234567890", "Anonymous"},
                                                                     {2, "9876543210", "Lazarus"}};

        m_body = new PhoneBookSetting(PhoneBookSetting::AppendPhoneBook, contacts);
        m_rawData = {0x2,  0x2,  0x1,  0xa,  0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x9,
                     0x41, 0x6e, 0x6f, 0x6e, 0x79, 0x6d, 0x6f, 0x75, 0x73, 0x2,  0xa,  0x39, 0x38, 0x37, 0x36,
                     0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x7,  0x4c, 0x61, 0x7a, 0x61, 0x72, 0x75, 0x73};
        m_object =
            Json::object({{"type", PhoneBookSetting::AppendPhoneBook},
                          {"length", 2},
                          {"contacts",
                           Json::array({Json::object({{"type", 1}, {"phone", "1234567890"}, {"name", "Anonymous"}}),
                                        Json::object({{"type", 2}, {"phone", "9876543210"}, {"name", "Lazarus"}})})}});
    }
};

TEST_F(PhoneBookSettingTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(PhoneBookSettingTest, TestPackage)
{
    TestPackage();
}

TEST_F(PhoneBookSettingTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(PhoneBookSettingTest, TestToJson)
{
    TestToJson();
}

}
