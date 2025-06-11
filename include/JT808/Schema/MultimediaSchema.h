#ifndef MULTIMEDIASCHEMA_H
#define MULTIMEDIASCHEMA_H

#include "JT808/Common.h"
#include "LocationInformationSchema.h"

namespace Schema {
static Json MultimediaEventInformationSchema = R"(
{
    "id": {
        "description": "Multimedia Data ID",
        "type": "number"
    },
    "type": {
        "description": "Multimedia Type",
        "type": "number"
    },
    "format": {
        "description": "Multimedia Encoding Format",
        "type": "number"
    },
    "event": {
        "description": "Event Item Code",
        "type": "number"
    },
    "channel": {
        "description": "Channel ID",
        "type": "number"
    }
}

)"_json;

static Json MultimediaRetrievalDataSchema = Json::object(
    {{"id", Json::object({{"description", "Multimedia ID"}, {"type", "number"}})},
     {"type", Json::object({{"description", "Multimedia Type"}, {"type", "number"}})},
     {"channel", Json::object({{"description", "Channel ID"}, {"type", "number"}})},
     {"event", Json::object({{"description", "Event Item Code"}, {"type", "number"}})},
     {"location",
      Json::object(
          {{"description", "Location Reporting"},
           {"type", "object"},
           {"properties", LocationInformationSchema},
           {"required", {"alarm", "status", "latitude", "longitude", "altitude", "speed", "bearing", "time"}}})}});

}
#endif // MULTIMEDIASCHEMA_H
