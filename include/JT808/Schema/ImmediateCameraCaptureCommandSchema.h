#ifndef IMMEDIATECAMERACAPTURECOMMANDSCHEMA_H
#define IMMEDIATECAMERACAPTURECOMMANDSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json ImmediateCameraCaptureCommandSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Immediate Camera Capture Command",
    "properties": {
        "channel": {
            "description": "Channel ID",
            "type": "number"
        },
        "command": {
            "description": "Capture Command",
            "type": "number"
        },
        "period": {
            "description": "Interval/Recording Time",
            "type": "number"
        },
        "saving": {
            "description": "Save Flag",
            "type": "number"
        },
        "resolution": {
            "description": "Resolution",
            "type": "number"
        },
        "quality": {
            "description": "Image/Video Quality",
            "type": "number"
        },
        "brightness": {
            "description": "Brightness",
            "type": "number"
        },
        "contrast": {
            "description": "Contrast",
            "type": "number"
        },
        "saturation": {
            "description": "Saturation",
            "type": "number"
        },
        "chroma": {
            "description": "Chromaticity",
            "type": "number"
        }
    },
    "required": ["channel", "command", "period", "saving", "resolution", "quality", "brightness", "contrast", "saturation", "chroma"],
    "type": "object"
}

)"_json;

}
#endif // IMMEDIATECAMERACAPTURECOMMANDSCHEMA_H
