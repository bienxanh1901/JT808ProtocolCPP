#ifndef RSAPUBLICKEYSCHEMA_H
#define RSAPUBLICKEYSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json RSAPublicKeySchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "RSA Public Key ",
    "properties": {
        "data": {
            "description": "Key data",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["data"],
    "type": "object"
}

)"_json;

}
#endif // RSAPUBLICKEYSCHEMA_H
