#ifndef TERMINALPROPERTIESQUERYRESPONSESCHEMA_H
#define TERMINALPROPERTIESQUERYRESPONSESCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json TerminalPropertiesQueryResponseSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Query Terminal Property Response",
    "properties": {
        "type": {
            "description": "Terminal Type",
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
            "type": "string"
        },
        "id": {
            "description": "Terminal ID",
            "type": "string"
        },
        "iccid": {
            "description": "Terminal SIM Card ICCID",
            "type": "string",
            "minLength": 18,
            "maxLength": 22
        },
        "hardware_version": {
            "description": "Terminal Hardware Version Number",
            "type": "string"
        },
        "firmware_version": {
            "description": "Terminal Firmware Number",
            "type": "string"
        },
        "gnss_prop": {
            "description": "GNSS Module Properties",
            "type": "number"
        },
        "comm_prop": {
            "description": "Communication Module Properties",
            "type": "number"
        }
    },
    "required": ["type", "manufacturer", "model", "id", "iccid", "hardware_version", "firmware_version", "gnss_prop", "comm_prop"],
    "type": "object"
}

)"_json;

}
#endif // TERMINALPROPERTIESQUERYRESPONSESCHEMA_H
