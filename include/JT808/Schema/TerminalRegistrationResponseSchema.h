#ifndef TERMINALREGISTRATIONRESPONSESCHEMA_H
#define TERMINALREGISTRATIONRESPONSESCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json TerminalRegistrationResponseSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Terminal Registration Response Body",
    "properties": {
        "seq": {
            "description": "Response Serial Number",
            "type": "number"
        },
        "result": {
            "description": "Response Result",
            "type": "number",
            "minimum": 0,
            "maximum": 4
        },
        "auth_code": {
            "description": "Authentication Code",
            "type": "string"
        }
    },
    "required": ["seq", "result"],
    "type": "object"
}

)"_json;

}
#endif // TERMINALREGISTRATIONRESPONSESCHEMA_H
