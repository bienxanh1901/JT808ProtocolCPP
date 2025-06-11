
#include "JT808/MessageBody/DriverIdentityInformationReport.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class DriverIdentityInformationReportTest : public MessageBodyBaseTest<DriverIdentityInformationReport>
{
protected:
    void SetUp() override
    {
        m_body = new DriverIdentityInformationReport(DriverIdentityInformationReport::ICCardAdded, "250501000000",
                                                     DriverIdentityInformationReport::Successful, "John Snow",
                                                     "123456789", "JT808", "20260100");
        m_rawData = {0x1,  0x25, 0x5,  0x1,  0x0,  0x0,  0x0,  0x0,  0x9,  0x4a, 0x6f, 0x68, 0x6e, 0x20, 0x53, 0x6e,
                     0x6f, 0x77, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x0,  0x0,  0x0,  0x0,  0x0,
                     0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x5,  0x4a, 0x54, 0x38, 0x30, 0x38, 0x20, 0x26, 0x1,  0x0};
        m_object = Json::object({{"status", DriverIdentityInformationReport::ICCardAdded},
                                 {"time", "250501000000"},
                                 {"ic_result", DriverIdentityInformationReport::Successful},
                                 {"driver_name", "John Snow"},
                                 {"certificate", "123456789"},
                                 {"organization", "JT808"},
                                 {"cert_expiry", "20260100"}});
    }
};

TEST_F(DriverIdentityInformationReportTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(DriverIdentityInformationReportTest, TestPackage)
{
    TestPackage();
}

TEST_F(DriverIdentityInformationReportTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(DriverIdentityInformationReportTest, TestToJson)
{
    TestToJson();
}

}
