#ifndef TERMINALUPGRADEPACKAGERESULTSCHEMA_H
#define TERMINALUPGRADEPACKAGERESULTSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json TerminalUpgradePackageResultSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Terminal Upgrade Result Notification",
    "properties": {
        "type": {
            "description": "Upgrade Type",
            "type": "number",
            "minimum": 0,
            "maximum": 52
        },
        "result": {
            "description": "Upgrade Result",
            "type": "number",
            "minimum": 0,
            "maximum": 2
        }
    },
    "required": ["type", "result"],
    "type": "object"
}

)"_json;

}
#endif // TERMINALUPGRADEPACKAGERESULTSCHEMA_H
