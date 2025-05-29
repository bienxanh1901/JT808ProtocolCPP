#ifndef TERMINALCONTROLSCHEMA_H
#define TERMINALCONTROLSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json TerminalControlSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Terminal Control Body",
    "properties": {
        "command": {
            "description": "Command Word",
            "type": "number"
        },
        "param": {
            "description": "Command Parameter",
            "type": "string"
        }
    },
    "required": ["command"],
    "type": "object"
}

)"_json;

}
#endif // TERMINALCONTROLSCHEMA_H
