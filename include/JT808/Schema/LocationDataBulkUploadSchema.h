#ifndef LOCATIONDATABULKUPLOADSCHEMA_H
#define LOCATIONDATABULKUPLOADSCHEMA_H

#include "LocationInformationSchema.h"
#include "nlohmann/json.hpp"

namespace Schema {
static nlohmann::json LocationDataBulkUploadSchema = nlohmann::json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Bulk Upload of Location Data"},
     {"properties",
      nlohmann::json::object(
          {{"type", nlohmann::json::object({{"description", "Location Data Type"}, {"type", "number"}})},
           {"length", nlohmann::json::object({{"description", "Number of Data Items"}, {"type", "number"}})},
           {"locations",
            nlohmann::json::object(
                {{"description", "Location Reporting Data Items"},
                 {"type", "array"},
                 {"items",
                  nlohmann::json::object(
                      {{"type", "object"}, {"properties", LocationInformationSchema}, {"required", {"basic"}}})}})}})},
     {"required", {"type", "length", "locations"}},
     {"type", "object"}});

}
#endif // LOCATIONDATABULKUPLOADSCHEMA_H
