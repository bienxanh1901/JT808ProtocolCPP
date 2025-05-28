
#include "JT808/MessageBody/DataTransmission.h"
#include "MessageBodyBaseTest.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {
class DataTransmissionTest : public MessageBodyBaseTest<DataTransmission>
{
protected:
    void SetUp() override
    {
        std::vector<uint8_t> const data {0x01, 0x03, 0x02, 0x05, 0x11, 0x22, 0x33, 0x44, 0x55};
        m_body = new DataTransmission(0x00, data);
        m_rawData = {0x0, 0x1, 0x3, 0x2, 0x5, 0x11, 0x22, 0x33, 0x44, 0x55};
    }
};

TEST_F(DataTransmissionTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(DataTransmissionTest, TestPackage)
{
    TestPackage();
}

}
