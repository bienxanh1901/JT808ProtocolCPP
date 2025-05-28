#ifndef MESSAGEBODYBASE_H
#define MESSAGEBODYBASE_H

#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class MessageBodyBase
{

public:
    MessageBodyBase() = default;
    virtual void parse(const std::vector<uint8_t>& data);
    virtual void parse(const uint8_t* data, int size);
    virtual std::vector<uint8_t> package();

    bool isValid() const;
    void setIsValid(bool newIsValid);

private:
    bool m_isValid = false;
};

}
#endif // MESSAGEBODYBASE_H
