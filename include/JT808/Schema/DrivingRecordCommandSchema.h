#ifndef DRIVINGRECORDCOMMANDSCHEMA_H
#define DRIVINGRECORDCOMMANDSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json DrivingRecordCommandSchema = R"(
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
