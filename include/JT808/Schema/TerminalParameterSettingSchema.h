#ifndef TERMINALPARAMETERSETTINGSCHEMA_H
#define TERMINALPARAMETERSETTINGSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json TerminalParameterSettingSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Set Terminal Parameters",
    "properties": {
        "length": {
            "description": "Total Number of Parameters",
            "type": "number"
        },
        "params": {
            "description": "Parameter Item List",
            "type": "array",
            "items": {
                "type": "object",
                "properties": {
                    "id": {
                        "description": "Parameter Item",
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
    "required": ["length", "params"],
    "type": "object"
}

)"_json;

}
#endif // TERMINALPARAMETERSETTINGSCHEMA_H
