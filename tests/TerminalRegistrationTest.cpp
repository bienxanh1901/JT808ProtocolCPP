
#include "JT808/MessageBody/TerminalRegistration.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class TerminalRegistrationTest : public MessageBodyBaseTest<TerminalRegistration>
{
protected:
    void SetUp() override
    {
        m_body = new TerminalRegistration(64, 24, "JMIOT", "JMVT01", "ID001", Yellow, "86B7-15262");
        m_rawData = {0x0,  0x40, 0x0, 0x18, 0x4a, 0x4d, 0x49, 0x4f, 0x54, 0x4a, 0x4d, 0x56, 0x54, 0x30, 0x31, 0x0,
                     0x0,  0x0,  0x0, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x49, 0x44, 0x30,
                     0x30, 0x31, 0x0, 0x0,  0x2,  0x38, 0x36, 0x42, 0x37, 0x2d, 0x31, 0x35, 0x32, 0x36, 0x32};
        m_object = nlohmann::json::object({{"province", 64},
                                           {"city", 24},
                                           {"manufacturer", "JMIOT"},
                                           {"model", "JMVT01"},
                                           {"id", "ID001"},
                                           {"color", Yellow},
                                           {"license_number", "86B7-15262"}});
    }
};

TEST_F(TerminalRegistrationTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalRegistrationTest, TestPackage)
{
    TestPackage();
}

TEST_F(TerminalRegistrationTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(TerminalRegistrationTest, TestToJson)
{
    TestToJson();
}

}
