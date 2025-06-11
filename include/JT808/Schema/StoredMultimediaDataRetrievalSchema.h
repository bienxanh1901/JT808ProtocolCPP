#ifndef STOREDMULTIMEDIADATARETRIEVALSCHEMA_H
#define STOREDMULTIMEDIADATARETRIEVALSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json StoredMultimediaDataRetrievalSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Storage Multimedia Data Retrieval",
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
        }
    },
    "required": ["type", "channel", "event", "start_time", "end_time"],
    "type": "object"
}

)"_json;

}
#endif // STOREDMULTIMEDIADATARETRIEVALSCHEMA_H
