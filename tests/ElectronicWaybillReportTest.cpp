
#include "JT808/MessageBody/ElectronicWaybillReport.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class ElectronicWaybillReportTest : public MessageBodyBaseTest<ElectronicWaybillReport>
{
protected:
    void SetUp() override
    {
        m_body = new ElectronicWaybillReport("ElectronicWaybillReport");
        m_rawData = {0x0,  0x0,  0x0,  0x17, 0x45, 0x6c, 0x65, 0x63, 0x74, 0x72, 0x6f, 0x6e, 0x69, 0x63,
                     0x57, 0x61, 0x79, 0x62, 0x69, 0x6c, 0x6c, 0x52, 0x65, 0x70, 0x6f, 0x72, 0x74};
    }
};

TEST_F(ElectronicWaybillReportTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(ElectronicWaybillReportTest, TestPackage)
{
    TestPackage();
}

}
