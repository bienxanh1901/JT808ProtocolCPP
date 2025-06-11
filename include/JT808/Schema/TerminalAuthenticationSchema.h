#ifndef TERMINALAUTHENTICATIONSCHEMA_H
#define TERMINALAUTHENTICATIONSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json TerminalAuthenticationSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Terminal Authentication Body",
    "properties": {
        "auth_code": {
            "description": "Authentication Code",
            "type": "string"
        }
    },
    "required": ["auth_code"],
    "type": "object"
}

)"_json;

}
#endif // TERMINALAUTHENTICATIONSCHEMA_H
