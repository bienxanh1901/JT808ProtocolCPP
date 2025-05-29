#ifndef MESSAGEBODYBASE_H
#define MESSAGEBODYBASE_H

#include "nlohmann/json-schema.hpp"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class MessageBodyBase
{

public:
    MessageBodyBase(const nlohmann::json& schema);
    virtual void parse(const std::vector<uint8_t>& data);
    virtual void parse(const uint8_t* data, int size);
    virtual std::vector<uint8_t> package();

    virtual void fromJson(const nlohmann::json& data);
    virtual nlohmann::json toJson();

    bool isValid() const;
    void setIsValid(bool newIsValid);

protected:
    bool validate(const nlohmann::json& data);

private:
    bool m_isValid = false;
    nlohmann::json_schema::json_validator m_validator;
};

}
#endif // MESSAGEBODYBASE_H
