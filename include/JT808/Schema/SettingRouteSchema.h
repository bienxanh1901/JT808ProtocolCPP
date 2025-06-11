#ifndef SETTINGROUTESCHEMA_H
#define SETTINGROUTESCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json SettingRouteSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Setting Route",
    "properties": {
        "id": {
            "description": "Route ID",
            "type": "number"
        },
        "flag": {
            "description": "Route Property",
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
        "length": {
            "description": "Total Number of Turning Points",
            "type": "number"
        },
        "points": {
            "description": "Turning Point Item",
            "type": "array",
            "items": {
                "type": "object",
                "properties": {
                    "point_id": {
                        "description": "Turning Point ID",
                        "type": "number"
                    },
                    "route_id": {
                        "description": "LatituSegment IDde",
                        "type": "number"
                    },
                    "lat": {
                        "description": "Turning Point Latitude",
                        "type": "number"
                    },
                    "lng": {
                        "description": "Turning Point Longitude",
                        "type": "number"
                    },
                    "width": {
                        "description": "Segment Width",
                        "type": "number"
                    },
                    "flag": {
                        "description": "Segment Property",
                        "type": "number"
                    },
                    "passed": {
                        "description": "Overlong Threshold for Segment Driving",
                        "type": "number"
                    },
                    "uncovered": {
                        "description": "Insufficient Threshold for Segment Driving",
                        "type": "number"
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
                "required": ["point_id", "route_id", "lat", "lng", "width", "flag"]
            }
        }
    },
    "required": ["id", "flag", "length", "points"],
    "type": "object"
}

)"_json;

}
#endif // SETTINGROUTESCHEMA_H
