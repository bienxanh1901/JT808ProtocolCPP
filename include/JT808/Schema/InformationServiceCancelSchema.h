#ifndef INFORMATIONSERVICECANCELSCHEMA_H
#define INFORMATIONSERVICECANCELSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json InformationServiceCancelSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Information Service/Cancel ",
    "properties": {
        "id": {
            "description": "Info Type",
            "type": "number"
        },
        "flag": {
            "description": "Dial/Cancel Flag",
            "type": "number"

        }
    },
    "required": ["id", "flag"],
    "type": "object"
}

)"_json;

}
#endif // INFORMATIONSERVICECANCELSCHEMA_H
