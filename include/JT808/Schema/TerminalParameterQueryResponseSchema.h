#ifndef TERMINALPARAMETERQUERYRESPONSESCHEMA_H
#define TERMINALPARAMETERQUERYRESPONSESCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json TerminalParameterQueryResponseSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Terminal Parameter Query Response Body",
    "properties": {
        "seq": {
            "description": "Response Serial Number",
            "type": "number"
        },
        "length": {
            "description": "Number of Response Parameters",
            "type": "number"
        },
        "params": {
            "description": "Parameter Item List",
            "type": "array",
            "items": {
                "description": "Parameter Item",
                "type": "object",
                "properties": {
                    "id": {
                        "description": "Parameter Id",
                        "type": "number"
                    },
                    "value": {
                        "description": "Parameter Value",
                        "type": ["number", "string", "array"]
                    }
                },
                "required": ["id", "value"]
            }
        }
    },
    "required": ["seq", "length", "params"],
    "type": "object"
}

)"_json;

}
#endif // TERMINALPARAMETERQUERYRESPONSESCHEMA_H
