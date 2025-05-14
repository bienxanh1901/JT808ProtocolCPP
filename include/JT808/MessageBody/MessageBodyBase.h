#ifndef MESSAGEBODYBASE_H
#define MESSAGEBODYBASE_H

#include <stdint.h>
#include <vector>

namespace JT808 {
namespace MessageBody {

class MessageBodyBase
{

public:
    MessageBodyBase(const std::vector<uint8_t>& data = {});
    MessageBodyBase(uint8_t* data, int size);

    virtual void parse();
    virtual void package();

public:
    bool isValid() const;

    std::vector<uint8_t> rawData() const;
    void setRawData(const std::vector<uint8_t>& newRawData);

protected:
    bool m_isValid = false;
    std::vector<uint8_t> m_rawData = {0};
};

}
}
#endif // MESSAGEBODYBASE_H
