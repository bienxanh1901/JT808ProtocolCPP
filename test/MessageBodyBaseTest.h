#ifndef MESSAGEBODYBASETEST_H
#define MESSAGEBODYBASETEST_H
#include "JT808/Utils.h"
#include <gtest/gtest.h>

namespace JT808 {
namespace MessageBody {

template<class T>
class MessageBodyBaseTest : public testing::Test
{
protected:
    ~MessageBodyBaseTest() override { }

    virtual void SetUp() override
    {
        m_body = new T();
    }

    void TearDown() override
    {
        delete m_body;
    }

    void TestPackage()
    {
        m_body->package();

        // Utils::printHexArray(m_body->rawData(), std::cout);
        // std::cout << std::endl;

        EXPECT_TRUE(m_body->isValid());
        EXPECT_EQ(m_body->rawData().size(), m_rawData.size());
        EXPECT_EQ(m_body->rawData(), m_rawData);
    }

    std::vector<uint8_t> m_rawData {};
    T* m_body;
};

}
}

#endif // MESSAGEBODYBASETEST_H
