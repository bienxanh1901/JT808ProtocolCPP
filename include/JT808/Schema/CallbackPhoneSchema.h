#ifndef CALLBACKPHONESCHEMA_H
#define CALLBACKPHONESCHEMA_H

#include "JT808/Common.h"

namespace Schema {
static Json CallbackPhoneSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Callback Phone",
    "properties": {
        "type": {
            "description": "Flag",
            "type": "number"
        },
        "phone": {
            "description": "Phone Number",
            "type": "string"
        }
    },
    "required": ["type", "phone"],
    "type": "object"
}

)"_json;

}
#endif // CALLBACKPHONESCHEMA_H
