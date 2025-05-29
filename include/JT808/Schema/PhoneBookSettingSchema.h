#ifndef PHONEBOOKSETTINGSCHEMA_H
#define PHONEBOOKSETTINGSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json PhoneBookSettingSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Phonebook Setting",
    "properties": {
        "type": {
            "description": "Setting Type",
            "type": "number"
        },
        "length": {
            "description": "Total Contacts",
            "type": "number"
        },
        "contacts": {
            "description": "Contact Item",
            "type": "array",
            "items": {
            "type": "object",
            "properties": {
                "type": {
                    "description": "Flag",
                    "type": "number"
                },
                "phone": {
                    "description": "Phone Number",
                    "type": "string"
                },
                "name": {
                    "description": "Contact",
                    "type": "string"
                }
            },
            "required": ["type", "phone", "name"]
        }
        }
    },
    "required": ["type", "length", "contacts"],
    "type": "object"
}

)"_json;

}
#endif // PHONEBOOKSETTINGSCHEMA_H
