
#include "JT808/MessageBody/TerminalUpgradePackage.h"
#include "MessageBodyBaseTest.h"
#include <gtest/gtest.h>

namespace JT808::MessageBody {
class TerminalUpgradePackageTest : public MessageBodyBaseTest<TerminalUpgradePackage>
{
protected:
    void SetUp() override
    {
        m_body = new TerminalUpgradePackage(Terminal, "JMIOT", "1.0.0", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        m_rawData = {0x0, 0x4a, 0x4d, 0x49, 0x4f, 0x54, 0x5, 0x31, 0x2e, 0x30, 0x2e, 0x30, 0x0,
                     0x0, 0x0,  0xa,  0x1,  0x2,  0x3,  0x4, 0x5,  0x6,  0x7,  0x8,  0x9,  0xa};
        m_object = nlohmann::json::object({{"type", Terminal},
                                           {"manufacturer", "JMIOT"},
                                           {"version", "1.0.0"},
                                           {"fw_length", 10},
                                           {"firmware", nlohmann::json::array({1, 2, 3, 4, 5, 6, 7, 8, 9, 10})}});
    }
};

TEST_F(TerminalUpgradePackageTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(TerminalUpgradePackageTest, TestPackage)
{
    TestPackage();
}

TEST_F(TerminalUpgradePackageTest, TestFromJsom)
{
    TestFromJson();
}

TEST_F(TerminalUpgradePackageTest, TestToJson)
{
    TestToJson();
}

}
