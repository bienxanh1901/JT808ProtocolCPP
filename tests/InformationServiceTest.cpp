
#include "JT808/MessageBody/InformationService.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class InformationServiceTest : public MessageBodyBaseTest<InformationService>
{
protected:
    ~InformationServiceTest() override { }

    void SetUp() override
    {
        m_body = new InformationService(123, "Hello World");
        m_rawData = {0x7b, 0x0, 0xb, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64};
    }
};

TEST_F(InformationServiceTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(InformationServiceTest, TestPackage)
{
    TestPackage();
}

}
