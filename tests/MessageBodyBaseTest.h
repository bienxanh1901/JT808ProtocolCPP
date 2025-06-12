#ifndef MESSAGEBODYBASETEST_H
#define MESSAGEBODYBASETEST_H
#include "JT808/Utils.h"
#include <gtest/gtest.h>
#include <iostream>
#include <ostream>

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
        ByteArray result = m_body->package();

        Utils::printHexArray(result, std::cout);
        std::cout << '\n';

        EXPECT_EQ(result.size(), m_rawData.size());
        EXPECT_EQ(result, m_rawData);
    }

    virtual void TestFromJson()
    {
        T body;
        body.fromJson(m_object);
        EXPECT_TRUE(body.isValid());
        EXPECT_TRUE(m_body->operator==(body));
    }

    virtual void TestToJson()
    {
        Json object = m_body->toJson();
        EXPECT_EQ(m_object, object);
    }

    ByteArray m_rawData;
    Json m_object;
    T* m_body;
};

}

#endif // MESSAGEBODYBASETEST_H
