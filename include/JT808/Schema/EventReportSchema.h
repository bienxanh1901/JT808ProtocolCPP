#ifndef EVENTREPORTSCHEMA_H
#define EVENTREPORTSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json EventReportSchema = R"(
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
