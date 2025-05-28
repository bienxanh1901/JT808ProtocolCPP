
#include "JT808/MessageBody/QuestionDispatch.h"
#include "MessageBodyBaseTest.h"

namespace JT808::MessageBody {
class QuestionDispatchTest : public MessageBodyBaseTest<QuestionDispatch>
{
protected:
    ~QuestionDispatchTest() override { }

    void SetUp() override
    {
        QuestionDispatch::Flag flag {.bits {.sos = 1, .terminalTTS = 1}};
        std::vector<QuestionDispatch::Answer> answers = {{0, "Answer 1"}, {1, "Answer Hello"}};
        m_body = new QuestionDispatch(flag, "Test Question", answers);
        m_rawData = {0x9,  0xd,  0x54, 0x65, 0x73, 0x74, 0x20, 0x51, 0x75, 0x65, 0x73, 0x74, 0x69, 0x6f,
                     0x6e, 0x0,  0x0,  0x8,  0x41, 0x6e, 0x73, 0x77, 0x65, 0x72, 0x20, 0x31, 0x1,  0x0,
                     0xc,  0x41, 0x6e, 0x73, 0x77, 0x65, 0x72, 0x20, 0x48, 0x65, 0x6c, 0x6c, 0x6f};
    }
};

TEST_F(QuestionDispatchTest, TestParseSuccess)
{
    TestParse();
}

TEST_F(QuestionDispatchTest, TestPackage)
{
    TestPackage();
}

}
