#ifndef GENERALRESPONSESCHEMA_H
#define GENERALRESPONSESCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json GeneralResponseSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "General Response Body",
    "properties": {
        "seq": {
            "description": "Response Serial Number",
            "type": "number"
        },
        "id": {
            "description": "Message Id",
            "type": "number",
            "minumum": 1
        },
        "result": {
            "description": "Response Result",
            "type": "number",
            "minimum": 0,
            "maximum": 4
        }
    },
    "required": ["seq", "id", "result"],
    "type": "object"
}

)"_json;

}
#endif // GENERALRESPONSESCHEMA_H
