#ifndef DRIVINGRECORDDATAUPLOADSCHEMA_H
#define DRIVINGRECORDDATAUPLOADSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json DrivingRecordDataUploadSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Driving Record Data Upload ",
    "properties": {
        "seq": {
            "description": "Response Serial Number",
            "type": "number"
        },
        "command": {
            "description": "Command",
            "type": "number"
        },
        "data": {
            "description": "Data Block",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["seq", "command", "data"],
    "type": "object"
}

)"_json;

}
#endif // DRIVINGRECORDDATAUPLOADSCHEMA_H
