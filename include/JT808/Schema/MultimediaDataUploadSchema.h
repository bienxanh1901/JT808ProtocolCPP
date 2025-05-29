#ifndef MULTIMEDIADATAUPLOADSCHEMA_H
#define MULTIMEDIADATAUPLOADSCHEMA_H

#include "LocationInformationSchema.h"
#include "MultimediaSchema.h"
#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json MultimediaDataUploadSchema = nlohmann::json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Multimedia Data Upload"},
     {"properties",
      nlohmann::json::object({
          {"info",
           nlohmann::json::object({{"description", "Multimedia Information"},
                                   {"type", "object"},
                                   {"properties", MultimediaEventInformationSchema},
                                   {"required", {"id", "type", "format", "event", "channel"}}})},
          {"location",
           nlohmann::json::object(
               {{"description", "Location Information"},
                {"type", "object"},
                {"properties", LocationInformationSchema},
                {"required", {"alarm", "status", "latitude", "longitude", "altitude", "speed", "bearing", "time"}}})},
          {"multimedia",
           nlohmann::json::object({
               {"description", "Multimedia Data Package"},
               {"type", "array"},
               {"items", nlohmann::json::object({{"type", "number"}})},
           })},
      })},
     {"required", {"info", "location", "multimedia"}},
     {"type", "object"}});

}
#endif // MULTIMEDIADATAUPLOADSCHEMA_H
