#ifndef AUDIORECORDINGSTARTCOMMANDSCHEMA_H
#define AUDIORECORDINGSTARTCOMMANDSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json AudioRecordingStartCommandSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Audio Recording Start Command",
    "properties": {
        "command": {
            "description": "Recording Command",
            "type": "number",
            "minimum": 0,
            "maximum": 1
        },
        "time": {
            "description": "Recording Time",
            "type": "number"
        },
        "saving": {
            "description": "Save Flag",
            "type": "number"
        },
        "rate": {
            "description": "Audio Sampling Rate",
            "type": "number"
        }
    },
    "required": ["command", "time", "saving", "rate"],
    "type": "object"
}

)"_json;

}
#endif // AUDIORECORDINGSTARTCOMMANDSCHEMA_H
