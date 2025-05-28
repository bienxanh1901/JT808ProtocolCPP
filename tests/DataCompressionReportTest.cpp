
#include "JT808/MessageBody/DataCompressionReport.h"
#include "MessageBodyBaseTest.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class DataCompressionReportTest : public MessageBodyBaseTest<DataCompressionReport>
{
protected:
    void SetUp() override
    {
        std::vector<uint8_t> const data {0x01, 0x03, 0x02, 0x05, 0x11, 0x22, 0x33, 0x44, 0x55};
        m_body = new DataCompressionReport(data);
        m_rawData = {0x0, 0x0, 0x0, 0x09, 0x1, 0x3, 0x2, 0x5, 0x11, 0x22, 0x33, 0x44, 0x55};
    }
};

TEST_F(DataCompressionReportTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(DataCompressionReportTest, TestPackage)
{
    TestPackage();
}

}
