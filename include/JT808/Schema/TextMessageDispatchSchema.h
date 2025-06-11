#ifndef TEXTMESSAGEDISPATCHSCHEMA_H
#define TEXTMESSAGEDISPATCHSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json TextMessageDispatchSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Text Message Dispatch",
    "properties": {
        "flag": {
            "description": "Flag",
            "type": "number"
        },
        "text": {
            "description": "Text Info",
            "type": "string"
        }
    },
    "required": ["flag", "text"],
    "type": "object"
}

)"_json;

}
#endif // TEXTMESSAGEDISPATCHSCHEMA_H
