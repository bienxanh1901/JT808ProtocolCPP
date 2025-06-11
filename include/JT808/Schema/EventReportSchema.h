#ifndef EVENTREPORTSCHEMA_H
#define EVENTREPORTSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json EventReportSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Event Report",
    "properties": {
        "id": {
            "description": "Event ID",
            "type": "number"
        }
    },
    "required": ["id"],
    "type": "object"
}

)"_json;

}
#endif // EVENTREPORTSCHEMA_H
