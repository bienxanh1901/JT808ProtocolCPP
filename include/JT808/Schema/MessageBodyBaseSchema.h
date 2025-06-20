#ifndef MESSAGEBODYBASESCHEMA_H
#define MESSAGEBODYBASESCHEMA_H

#include "JT808/Common.h"
#include "nlohmann/json.hpp"

namespace Schema {
static Json MessageBodyBaseSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "MessageBodyBase",
    "properties": {
        "data": {
            "description": "Body data",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "type": "object"
}

)"_json;

}
#endif // MESSAGEBODYBASESCHEMA_H
