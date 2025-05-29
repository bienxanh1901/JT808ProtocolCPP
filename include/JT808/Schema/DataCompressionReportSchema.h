#ifndef DATACOMPRESSIONREPORTSCHEMA_H
#define DATACOMPRESSIONREPORTSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json DataCompressionReportSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Data Compression Report ",
    "properties": {
        "data": {
            "description": "Compressed Message Body",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["data"],
    "type": "object"
}

)"_json;

}
#endif // DATACOMPRESSIONREPORTSCHEMA_H
