#ifndef GENERALRESPONSESCHEMA_H
#define GENERALRESPONSESCHEMA_H

#include "JT808/Common.h"
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
#endif // GENERALRESPONSESCHEMA_H
