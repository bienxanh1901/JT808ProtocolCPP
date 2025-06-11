#ifndef DRIVERIDENTITYINFORMATIONREPORTSCHEMA_H
#define DRIVERIDENTITYINFORMATIONREPORTSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json DriverIdentityInformationReportSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Driver Identity Information Collection Report",
    "properties": {
        "status": {
            "description": "Status",
            "type": "number"
        },
        "time": {
            "description": "Time",
            "type": "string"
        },
        "ic_result": {
            "description": "IC Card Read Result",
            "type": "number"
        },
        "driver_name": {
            "description": "Driver Name",
            "type": "string"
        },
        "certificate": {
            "description": "Professional Qualification Certificate Code",
            "type": "string"
        },
        "organization": {
            "description": "Issuing Authority Name",
            "type": "string"
        },
        "cert_expiry": {
            "description": "Certificate Validity",
            "type": "string"
        }
    },
    "required": ["status", "time", "ic_result"],
    "type": "object"
}

)"_json;

}
#endif // DRIVERIDENTITYINFORMATIONREPORTSCHEMA_H
