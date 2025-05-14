#ifndef MESSAGEBODYBASE_H
#define MESSAGEBODYBASE_H

#include <cstdint>
#include <vector>

#include <JT808/Utils.h>

namespace JT808::MessageBody {

class MessageBodyBase
{

public:
    MessageBodyBase();
    virtual void parse(const std::vector<uint8_t>& data);
    virtual void parse(const uint8_t* data, int size);
    virtual std::vector<uint8_t> package();

    bool isValid() const;
    void setIsValid(bool newIsValid);

private:
    bool m_isValid = false;
    Utils::U16Array m_u16Array;
    Utils::U32Array m_u32Array;
};

}
#endif // MESSAGEBODYBASE_H
