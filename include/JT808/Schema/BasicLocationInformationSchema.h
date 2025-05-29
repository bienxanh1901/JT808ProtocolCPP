#ifndef BASICLOCATIONINFORMATIONSCHEMA_H
#define BASICLOCATIONINFORMATIONSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json BasicLocationInformationSchema = R"(
{
    "type": "object",
    "properties": {
        "alarm": {
            "description": "Alarm Flag",
            "type": "number"
        },
        "status": {
            "description": "Status",
            "type": "number"
        },
        "latitude": {
            "description": "Latitude",
            "type": "number"
        },
        "longitude": {
            "description": "Longitude",
            "type": "number"
        },
        "altitude": {
            "description": "Altitude",
            "type": "number"
        },
        "speed": {
            "description": "Speed",
            "type": "number"
        },
        "bearing": {
            "description": "Direction",
            "type": "number"
        },
        "time": {
            "description": "Time",
            "type": "string"
        }
    },
    "required": ["alarm", "status", "latitude", "longitude", "altitude", "speed", "bearing", "time"]
}

)"_json;

}
#endif // BASICLOCATIONINFORMATIONSCHEMA_H
