#ifndef ELECTRONICWAYBILLREPORTSCHEMA_H
#define ELECTRONICWAYBILLREPORTSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json ElectronicWaybillReportSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Electronic Waybill Report",
    "properties": {
        "length": {
            "description": "Electronic Waybill Length",
            "type": "number"
        },
        "data": {
            "description": "Electronic Waybill Content",
            "type": "array",
            "items": {
                "type": "number"
            }
        }
    },
    "required": ["length", "data"],
    "type": "object"
}

)"_json;

}
#endif // ELECTRONICWAYBILLREPORTSCHEMA_H
