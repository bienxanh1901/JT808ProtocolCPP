#ifndef MULTIMEDIADATAUPLOADRESPONSESCHEMA_H
#define MULTIMEDIADATAUPLOADRESPONSESCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json MultimediaDataUploadResponseSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Response to Multimedia Data Upload",
    "properties": {
        "mm_id": {
            "description": "Multimedia ID",
            "type": "number"
        },
        "length": {
            "description": "Total Number of Retransmission Packages",
            "type": "number"
        },
        "retx_ids": {
            "description": "List of Retransmission Package IDs",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["mm_id", "length", "retx_ids"],
    "type": "object"
}

)"_json;

}
#endif // MULTIMEDIADATAUPLOADRESPONSESCHEMA_H
