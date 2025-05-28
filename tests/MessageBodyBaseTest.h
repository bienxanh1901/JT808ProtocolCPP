#ifndef MESSAGEBODYBASETEST_H
#define MESSAGEBODYBASETEST_H
// #include "JT808/Utils.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

namespace JT808::MessageBody {

template<class T>
class MessageBodyBaseTest : public testing::Test
{
protected:
    void SetUp() override
    {
        m_body = new T();
    }

    void TearDown() override
    {
        delete m_body;
    }

    virtual void TestParse()
    {
        T body;
        body.parse(m_rawData);

        EXPECT_TRUE(body.isValid());
        EXPECT_TRUE(m_body->operator==(body));
    }

    virtual void TestPackage()
    {
        std::vector<uint8_t> result = m_body->package();

        // Utils::printHexArray(result, std::cout);
        // std::cout << std::endl;

        EXPECT_EQ(result.size(), m_rawData.size());
        EXPECT_EQ(result, m_rawData);
    }

    std::vector<uint8_t> m_rawData;
    T* m_body;
};

}

#endif // MESSAGEBODYBASETEST_H
