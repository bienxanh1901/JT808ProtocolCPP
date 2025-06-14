#ifndef INFORMATIONSERVICESCHEMA_H
#define INFORMATIONSERVICESCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json InformationServiceSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Information Service",
    "properties": {
        "type": {
            "description": "Info Type",
            "type": "number"
        },
        "info": {
            "description": "Info Content",
            "type": "string"
        }
    },
    "required": ["type", "info"],
    "type": "object"
}

)"_json;

}
#endif // INFORMATIONSERVICESCHEMA_H
