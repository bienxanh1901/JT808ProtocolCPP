#ifndef MANUALALARMCONFIRMATIONSCHEMA_H
#define MANUALALARMCONFIRMATIONSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json ManualAlarmConfirmationSchema = R"(
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
