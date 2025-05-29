#ifndef MULTIMEDIASCHEMA_H
#define MULTIMEDIASCHEMA_H

#include "LocationInformationSchema.h"
#include "nlohmann/json.hpp"

namespace Schema {
static nlohmann::json MultimediaEventInformationSchema = R"(
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

static nlohmann::json MultimediaRetrievalDataSchema = nlohmann::json::object(
    {{"id", nlohmann::json::object({{"description", "Multimedia ID"}, {"type", "number"}})},
     {"type", nlohmann::json::object({{"description", "Multimedia Type"}, {"type", "number"}})},
     {"channel", nlohmann::json::object({{"description", "Channel ID"}, {"type", "number"}})},
     {"event", nlohmann::json::object({{"description", "Event Item Code"}, {"type", "number"}})},
     {"location",
      nlohmann::json::object(
          {{"description", "Location Reporting"},
           {"type", "object"},
           {"properties", LocationInformationSchema},
           {"required", {"alarm", "status", "latitude", "longitude", "altitude", "speed", "bearing", "time"}}})}});

}
#endif // MULTIMEDIASCHEMA_H
