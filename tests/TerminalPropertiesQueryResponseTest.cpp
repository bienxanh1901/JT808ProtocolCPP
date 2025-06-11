
#include "JT808/MessageBody/TerminalPropertiesQueryResponse.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class TerminalPropertiesQueryResponseTest : public MessageBodyBaseTest<TerminalPropertiesQueryResponse>
{
protected:
    void SetUp() override
    {
        m_body = new TerminalPropertiesQueryResponse({.value = 1}, "JMIOT", "JMVT01", "ID001", "89610000000000012345",
                                                     "1.1.0", "2.0.5", {.value = 128}, {.value = 64});
        m_rawData = {0x0,  0x1,  0x4a, 0x4d, 0x49, 0x4f, 0x54, 0x4a, 0x4d, 0x56, 0x54, 0x30, 0x31, 0x0,  0x0,
                     0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x49, 0x44, 0x30,
                     0x30, 0x31, 0x0,  0x0,  0x89, 0x61, 0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x23, 0x45, 0x5,
                     0x31, 0x2e, 0x31, 0x2e, 0x30, 0x5,  0x32, 0x2e, 0x30, 0x2e, 0x35, 0x80, 0x40};
        m_object = Json::object({{"type", 1},
                                 {"manufacturer", "JMIOT"},
                                 {"model", "JMVT01"},
                                 {"id", "ID001"},
                                 {"iccid", "89610000000000012345"},
                                 {"hardware_version", "1.1.0"},
                                 {"firmware_version", "2.0.5"},
                                 {"gnss_prop", 128},
                                 {"comm_prop", 64}});
    }
};

TEST_F(TerminalPropertiesQueryResponseTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalPropertiesQueryResponseTest, TestPackage)
{
    TestPackage();
}

TEST_F(TerminalPropertiesQueryResponseTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(TerminalPropertiesQueryResponseTest, TestToJson)
{
    TestToJson();
}

}
