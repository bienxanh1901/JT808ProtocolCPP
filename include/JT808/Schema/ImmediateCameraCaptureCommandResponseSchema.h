#ifndef IMMEDIATECAMERACAPTURECOMMANDRESPONSESCHEMA_H
#define IMMEDIATECAMERACAPTURECOMMANDRESPONSESCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json ImmediateCameraCaptureCommandResponseSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Immediate Camera Capture Response",
    "properties": {
        "seq": {
            "description": "Response Serial Number",
            "type": "number"
        },
        "result": {
            "description": "Result",
            "type": "number"
        },
        "length": {
            "description": "Number of Multimedia IDs",
            "type": "number"
        },
        "ids": {
            "description": "List of Multimedia IDs",
            "type": "array",
            "itmes": {
                "type": "number"
            }
        }
    },
    "required": ["seq", "length", "result"],
    "type": "object"
}

)"_json;

}
#endif // IMMEDIATECAMERACAPTURECOMMANDRESPONSESCHEMA_H
