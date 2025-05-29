#ifndef INFORMATIONSERVICEMENUSETTINGSCHEMA_H
#define INFORMATIONSERVICEMENUSETTINGSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json InformationServiceMenuSettingSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Information Service Menu Setting ",
    "properties": {
        "type": {
            "description": "Setting Type",
            "type": "number"
        },
        "length": {
            "description": "Total Info Items",
            "type": "number"
        },
        "menus": {
            "description": "Info Item List",
            "type": "array",
            "items": {
                "type": "object",
                "properties": {
                    "type": {
                        "description": "Info Type",
                        "type": "number"
                    },
                    "info": {
                        "description": "Info Name",
                        "type": "string"
                    }
                },
                "required": ["type", "info"]
            }
        }
    },
    "required": ["type", "length", "menus"],
    "type": "object"
}

)"_json;

}
#endif // INFORMATIONSERVICEMENUSETTINGSCHEMA_H
