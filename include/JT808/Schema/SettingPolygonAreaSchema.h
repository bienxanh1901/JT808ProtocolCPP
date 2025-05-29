#ifndef SETTINGPOLYGONAREASCHEMA_H
#define SETTINGPOLYGONAREASCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json SettingPolygonAreaSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Setting Polygonal Area",
    "properties": {
        "id": {
            "description": "Area ID",
            "type": "number"
        },
        "flag": {
            "description": "Area Property",
            "type": "number"
        },
        "start_time": {
            "description": "Start Time",
            "type": "string"
        },
        "end_time": {
            "description": "End Time",
            "type": "string"
        },
        "max_speed": {
            "description": "Maximum Speed",
            "type": "number"
        },
        "overspeed_duration": {
            "description": "Overspeed Duration",
            "type": "number"
        },
        "length": {
            "description": "Total Number of Vertices",
            "type": "number"
        },
        "points": {
            "description": "Area Item",
            "type": "array",
            "items": {
                "type": "object",
                "properties": {
                    "lat": {
                        "description": "Latitude",
                        "type": "number"
                    },
                    "lng": {
                        "description": "Longitude",
                        "type": "number"
                    }

                },
                "required": ["lat", "lng"]
            }
        }
    },
    "required": ["id", "flag", "length", "points"],
    "type": "object"
}

)"_json;

}
#endif // SETTINGPOLYGONAREASCHEMA_H
