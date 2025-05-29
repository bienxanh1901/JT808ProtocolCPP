#ifndef TEMPORARYLOCATIONTRACKINGCONTROLSCHEMA_H
#define TEMPORARYLOCATIONTRACKINGCONTROLSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json TemporaryLocationTrackingControlSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Temporary Location Tracking Control ",
    "properties": {
        "period": {
            "description": "Interval",
            "type": "number"
        },
        "expiry": {
            "description": "Tracking Duration",
            "type": "number"
        }
    },
    "required": ["period", "expiry"],
    "type": "object"
}

)"_json;

}
#endif // TEMPORARYLOCATIONTRACKINGCONTROLSCHEMA_H
