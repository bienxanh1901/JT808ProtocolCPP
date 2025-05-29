#ifndef TERMINALPARAMETERQUERYSCHEMA_H
#define TERMINALPARAMETERQUERYSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json TerminalParameterQuerySchema = R"(
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
