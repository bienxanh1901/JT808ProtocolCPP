#ifndef TERMINALUPGRADEPACKAGESCHEMA_H
#define TERMINALUPGRADEPACKAGESCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json TerminalUpgradePackageSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Terminal Upgrade Package Command",
    "properties": {
        "type": {
            "description": "Upgrade Type",
            "type": "number"
        },
        "manufacturer": {
            "description": "Manufacturer ID",
            "type": "string",
            "minLength": 5,
            "maxLength": 5

        },
        "version": {
            "description": "Version Number",
            "type": "string"
        },
        "fw_length": {
            "description": "Upgrade Package Length",
            "type": "number"
        },
        "firmware": {
            "description": "Upgrade Package",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["type", "manufacturer", "version", "fw_length", "firmware"],
    "type": "object"
}

)"_json;

}
#endif // TERMINALUPGRADEPACKAGESCHEMA_H
