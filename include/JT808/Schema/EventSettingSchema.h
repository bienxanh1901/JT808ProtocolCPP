#ifndef EVENTSETTINGSCHEMA_H
#define EVENTSETTINGSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json EventSettingSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Event Setting",
    "properties": {
        "type": {
            "description": "Setting Type",
            "type": "number"
        },
        "length": {
            "description": "Total Events",
            "type": "number"

        },
        "events": {
            "description": "Event List",
            "type": "array",
            "items": {
                "type": "object",
                "properties": {
                    "id": {
                        "description": "Event ID",
                        "type": "number"
                    },
                    "content": {
                        "description": "Event Content",
                        "type": "string"
                    }
                },
                "required": ["id", "content"]
            }
        }
    },
    "required": ["type"],
    "type": "object"
}

)"_json;

}
#endif // EVENTSETTINGSCHEMA_H
