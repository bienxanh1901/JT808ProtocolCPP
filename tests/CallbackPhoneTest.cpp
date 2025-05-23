
#include "JT808/MessageBody/CallbackPhone.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class CallbackPhoneTest : public MessageBodyBaseTest<CallbackPhone>
{
protected:
    ~CallbackPhoneTest() override { }

    void SetUp() override
    {
        m_body = new CallbackPhone(CallbackPhone::OrdinaryPhone, "1234567890");
        m_rawData = {0x0, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30};
    }
};

TEST_F(CallbackPhoneTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(CallbackPhoneTest, TestPackage)
{
    TestPackage();
}

}
