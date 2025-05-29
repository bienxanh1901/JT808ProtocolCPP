#ifndef VEHICLECONTROLSCHEMA_H
#define VEHICLECONTROLSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json VehicleControlSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Vehicle Control",
    "properties": {
        "flag": {
            "description": "Control Flag",
            "type": "number"
        }
    },
    "required": ["flag"],
    "type": "object"
}

)"_json;

}
#endif // VEHICLECONTROLSCHEMA_H
