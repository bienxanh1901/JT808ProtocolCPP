#ifndef SUBPACKAGERETRANSMISSIONREQUESTSCHEMA_H
#define SUBPACKAGERETRANSMISSIONREQUESTSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json SubPackageRetransmissionRequestSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Re-transmission Request for Sub-package",
    "properties": {
        "seq": {
            "description": "Original Message Serial Number",
            "type": "number"
        },
        "length": {
            "description": "Total Number of Re-transmission Packages",
            "type": "number"
        },
        "ids": {
            "description": "Re-transmission Package ID List",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["seq", "length", "ids"],
    "type": "object"
}

)"_json;

}
#endif // SUBPACKAGERETRANSMISSIONREQUESTSCHEMA_H
