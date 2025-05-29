#ifndef DELETINGAREAROUTESCHEMA_H
#define DELETINGAREAROUTESCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json DeletingAreaRouteSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "DeletingAreaRoute",
    "properties": {
        "length": {
            "description": "Number of Areas",
            "type": "number"
        },
        "ids": {
            "description": "List of Area IDs",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["length", "ids"],
    "type": "object"
}

)"_json;

}
#endif // DELETINGAREAROUTESCHEMA_H
