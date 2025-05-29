
#include "JT808/MessageBody/EventReport.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class EventReportTest : public MessageBodyBaseTest<EventReport>
{
protected:
    void SetUp() override
    {

        m_body = new EventReport(123);
        m_rawData = {0x7b};
        m_object = nlohmann::json::object({{"id", 123}});
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

TEST_F(EventReportTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(EventReportTest, TestToJson)
{
    TestToJson();
}

}
