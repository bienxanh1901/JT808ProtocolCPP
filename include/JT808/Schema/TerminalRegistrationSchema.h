#ifndef TERMINALREGISTRATIONSCHEMA_H
#define TERMINALREGISTRATIONSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json TerminalRegistrationSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Terminal Registration",
    "properties": {
        "province": {
            "description": "Province ID",
            "type": "number"
        },
        "city": {
            "description": "City ID",
            "type": "number"
        },
        "manufacturer": {
            "description": "Manufacturer ID",
            "type": "string",
            "minLength": 5,
            "maxLength": 5

        },
        "model": {
            "description": "Terminal Model",
            "type": "string",
            "minLength": 1,
            "maxLength": 20
        },
        "id": {
            "description": "Terminal ID",
            "type": "string",
            "minLength": 1,
            "maxLength": 7
        },
        "color": {
            "description": "Vehicle Color",
            "type": "number"
        },
        "license_number": {
            "description": "Vehicle Identification",
            "type": "string"
        }
    },
    "required": ["province", "city", "manufacturer", "model", "id", "color"],
    "type": "object"
}

)"_json;

}
#endif // TERMINALREGISTRATIONSCHEMA_H
