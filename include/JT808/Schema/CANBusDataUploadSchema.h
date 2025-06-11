#ifndef CANBUSDATAUPLOADSCHEMA_H
#define CANBUSDATAUPLOADSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json CANBusDataUploadSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "CAN Bus Data Upload",
    "properties": {
        "length": {
            "description": "Number of Data Items",
            "type": "number"
        },
        "time": {
            "description": "CAN Bus Data Reception Time",
            "type": "string"
        },
        "can_data": {
            "description": "CAN Bus Data Items",
            "type": "array",
            "items": {
                "type": "object",
                "properties": {
                    "channel": {
                        "description": "CAN Bus Channel Number",
                        "type": "number"
                    },
                    "frame_type": {
                        "description": "Frame Type",
                        "type": "number"
                    },
                    "data_method": {
                        "description": "Data Collection Method",
                        "type": "number"
                    },
                    "id": {
                        "description": "CAN Bus ID",
                        "type": "number"
                    },
                    "data": {
                        "description": "CAN Data",
                        "type": "string"
                    }
                },
                "required": ["channel", "frame_type", "data_method", "id", "data"]
            }
        }
    },
    "required": ["length", "time", "can_data"],
    "type": "object"
}

)"_json;

}
#endif // CANBUSDATAUPLOADSCHEMA_H
