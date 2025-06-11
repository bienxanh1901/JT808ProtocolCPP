#ifndef RSAPUBLICKEYSCHEMA_H
#define RSAPUBLICKEYSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json RSAPublicKeySchema = R"(
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
