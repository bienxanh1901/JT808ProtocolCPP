#ifndef DATATRANSMISSIONSCHEMA_H
#define DATATRANSMISSIONSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json DataTransmissionSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Data Transmission",
    "properties": {
        "type": {
            "description": "Transmitted Message Type",
            "type": "number"
        },
        "data": {
            "description": "Transmitted Message Content",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["type", "data"],
    "type": "object"
}

)"_json;

}
#endif // DATATRANSMISSIONSCHEMA_H
