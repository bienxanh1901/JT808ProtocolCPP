#ifndef MESSAGEBODYBASE_H
#define MESSAGEBODYBASE_H

#include "JT808/Common.h"
#include <cstdint>

namespace JT808::MessageBody {

class MessageBodyBase
{

public:
    MessageBodyBase();
    MessageBodyBase(const Json& schema);
    virtual void parse(const ByteArray& data);
    virtual void parse(const uint8_t* data, int size);
    virtual ByteArray package();

    virtual void fromJson(const Json& data);
    virtual Json toJson();

    bool isValid() const;
    void setIsValid(bool newIsValid);

protected:
    bool validate(const Json& data);

private:
    bool m_isValid = false;
    JsonValidator m_validator;
};

}
#endif // MESSAGEBODYBASE_H
