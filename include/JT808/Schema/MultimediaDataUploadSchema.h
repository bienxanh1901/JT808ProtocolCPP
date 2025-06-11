#ifndef MULTIMEDIADATAUPLOADSCHEMA_H
#define MULTIMEDIADATAUPLOADSCHEMA_H

#include "JT808/Common.h"
#include "LocationInformationSchema.h"
#include "MultimediaSchema.h"
namespace Schema {
static Json MultimediaDataUploadSchema = Json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Multimedia Data Upload"},
     {"properties",
      Json::object({
          {"info",
           Json::object({{"description", "Multimedia Information"},
                         {"type", "object"},
                         {"properties", MultimediaEventInformationSchema},
                         {"required", {"id", "type", "format", "event", "channel"}}})},
          {"location",
           Json::object(
               {{"description", "Location Information"},
                {"type", "object"},
                {"properties", LocationInformationSchema},
                {"required", {"alarm", "status", "latitude", "longitude", "altitude", "speed", "bearing", "time"}}})},
          {"multimedia",
           Json::object({
               {"description", "Multimedia Data Package"},
               {"type", "array"},
               {"items", Json::object({{"type", "number"}})},
           })},
      })},
     {"required", {"info", "location", "multimedia"}},
     {"type", "object"}});

}
#endif // MULTIMEDIADATAUPLOADSCHEMA_H
