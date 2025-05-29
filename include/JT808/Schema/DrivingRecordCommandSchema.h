#ifndef DRIVINGRECORDCOMMANDSCHEMA_H
#define DRIVINGRECORDCOMMANDSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json DrivingRecordCommandSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Driving Record Data Collection Command ",
    "properties": {
        "command": {
            "description": "Command",
            "type": "number"
        },
        "param": {
            "description": "Data Block",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["command", "param"],
    "type": "object"
}

)"_json;

}
#endif // DRIVINGRECORDCOMMANDSCHEMA_H
