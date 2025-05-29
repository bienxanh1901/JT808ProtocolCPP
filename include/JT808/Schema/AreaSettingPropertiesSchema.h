#ifndef AREASETTINGPROPERTIESSCHEMA_H
#define AREASETTINGPROPERTIESSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json CircularAreaSchema = R"(
{
    "properties": {
        "id": {
            "description": "Area ID",
            "type": "number"
        },
        "flag": {
            "description": "Area Property",
            "type": "number"
        },
        "center_lat": {
            "description": "Center Latitude",
            "type": "number"
        },
        "center_lng": {
            "description": "Center Longitude",
            "type": "number"
        },
        "radius": {
            "description": "Radius",
            "type": "number"
        },
        "start_time": {
            "description": "Start Time",
            "type": "string",
            "minLength": 12,
            "maxLength": 12
        },
        "end_time": {
            "description": "End Time",
            "type": "string",
            "minLength": 12,
            "maxLength": 12
        },
        "max_speed": {
            "description": "Maximum Speed",
            "type": "number"
        },
        "overspeed_duration": {
            "description": "Overspeed Duration",
            "type": "number"
        }
    },
    "required": ["id", "flag", "center_lat", "center_lng", "radius"],
    "type": "object"
}

)"_json;

static nlohmann::json RectangularAreaSchema = R"(
{
    "properties": {
        "id": {
            "description": "Area ID",
            "type": "number"
        },
        "flag": {
            "description": "Area Property",
            "type": "number"
        },
        "lt_lat": {
            "description": "Upper Left Latitude",
            "type": "number"
        },
        "lt_lng": {
            "description": "Upper Left Longitude",
            "type": "number"
        },
        "rb_lat": {
            "description": "Lower Right Latitude",
            "type": "number"
        },
        "rb_lng": {
            "description": "Lower Right Longitude",
            "type": "number"
        },
        "start_time": {
            "description": "Start Time",
            "type": "string",
            "minLength": 12,
            "maxLength": 12
        },
        "end_time": {
            "description": "End Time",
            "type": "string",
            "minLength": 12,
            "maxLength": 12
        },
        "max_speed": {
            "description": "Maximum Speed",
            "type": "number"
        },
        "overspeed_duration": {
            "description": "Overspeed Duration",
            "type": "number"
        }
    },
    "required": ["id", "flag", "lt_lat", "lt_lng", "rb_lat", "rb_lng"],
    "type": "object"
}

)"_json;

}
#endif // AREASETTINGPROPERTIESSCHEMA_H
