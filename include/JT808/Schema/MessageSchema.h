#ifndef MESSAGESCHEMA_H
#define MESSAGESCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json MessageSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "JT808 Message",
    "properties": {
        "header": {
            "description": "Message Header",
            "type": "object",
            "properties": {
                "id" : {
                    "description": "Message ID",
                    "type": "number"
                },
                "encrypt": {
                    "description": "encrypt flag",
                    "type": "number"
                },
                "length": {
                    "description": "Message Body Length",
                    "type": "number"
                },
                "phone": {
                    "description": "Terminal Phone Number",
                    "type": "string"
                },
                "seq": {
                    "description": "Message Sequence Number",
                    "type": "number"
                },
                "segment": {
                    "description": "Refer to sub-package message",
                    "type": "number"
                },
                "frag_total": {
                    "description": "Total number of sub package",
                    "type": "number"
                },
                "frag_seq": {
                    "description": "Sub package sequence number",
                    "type": "number"
                }
            },
            "required": ["id", "encrypt", "length", "phone", "seq"]
        },
        "body": {
            "description": "Message Body",
            "type": "object"
        }
    },
    "required": ["header"],
    "type": "object"
}


)"_json;

}
#endif // MESSAGESCHEMA_H
