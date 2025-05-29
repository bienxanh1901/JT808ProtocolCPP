#ifndef STOREDMULTIMEDIADATAUPLOADCOMMANDSCHEMA_H
#define STOREDMULTIMEDIADATAUPLOADCOMMANDSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json StoredMultimediaDataUploadCommandSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Command for Uploading Stored Multimedia Data",
    "properties": {
        "type": {
            "description": "Multimedia Type",
            "type": "number"
        },
        "channel": {
            "description": "Channel ID",
            "type": "number"
        },
        "event": {
            "description": "Event Item Code",
            "type": "number"
        },
        "start_time": {
            "description": "EStart Time",
            "type": "string"
        },
        "end_time": {
            "description": "End Time",
            "type": "string"
        },
        "delete": {
            "description": "Delete Flag",
            "type": "number"
        }
    },
    "required": ["type", "channel", "event", "start_time", "end_time", "delete"],
    "type": "object"
}

)"_json;

}
#endif // STOREDMULTIMEDIADATAUPLOADCOMMANDSCHEMA_H
