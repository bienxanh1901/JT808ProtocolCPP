#ifndef TERMINALPARAMETERQUERYSCHEMA_H
#define TERMINALPARAMETERQUERYSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json TerminalParameterQuerySchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Query Terminal Parameters Body",
    "properties": {
        "length": {
            "description": "Total Number of Parameters",
            "type": "number"
        },
        "ids": {
            "description": "Parameter Item List",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["length", "ids"],
    "type": "object"
}

)"_json;

}
#endif // TERMINALPARAMETERQUERYSCHEMA_H
