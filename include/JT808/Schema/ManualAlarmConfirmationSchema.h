#ifndef MANUALALARMCONFIRMATIONSCHEMA_H
#define MANUALALARMCONFIRMATIONSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json ManualAlarmConfirmationSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Alarm Message Seq",
    "properties": {
        "seq": {
            "description": "Response Serial Number",
            "type": "number"
        },
        "type": {
            "description": "Manual Alarm Type",
            "type": "number"
        }
    },
    "required": ["seq", "type"],
    "type": "object"
}

)"_json;

}
#endif // MANUALALARMCONFIRMATIONSCHEMA_H
