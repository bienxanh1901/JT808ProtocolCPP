
#include "JT808/MessageBody/EventReport.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class EventReportTest : public MessageBodyBaseTest<EventReport>
{
protected:
    ~EventReportTest() override { }

    void SetUp() override
    {

        m_body = new EventReport(123);
        m_rawData = {0x7b};
    }
};

TEST_F(EventReportTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(EventReportTest, TestPackage)
{
    TestPackage();
}

}
