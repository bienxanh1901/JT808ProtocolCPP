#ifndef TEMPORARYLOCATIONTRACKINGCONTROLSCHEMA_H
#define TEMPORARYLOCATIONTRACKINGCONTROLSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json TemporaryLocationTrackingControlSchema = R"(
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
