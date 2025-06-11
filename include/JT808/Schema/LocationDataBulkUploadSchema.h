#ifndef LOCATIONDATABULKUPLOADSCHEMA_H
#define LOCATIONDATABULKUPLOADSCHEMA_H

#include "JT808/Common.h"
#include "LocationInformationSchema.h"

namespace Schema {
static Json LocationDataBulkUploadSchema = Json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Bulk Upload of Location Data"},
     {"properties",
      Json::object({{"type", Json::object({{"description", "Location Data Type"}, {"type", "number"}})},
                    {"length", Json::object({{"description", "Number of Data Items"}, {"type", "number"}})},
                    {"locations",
                     Json::object({{"description", "Location Reporting Data Items"},
                                   {"type", "array"},
                                   {"items",
                                    Json::object({{"type", "object"},
                                                  {"properties", LocationInformationSchema},
                                                  {"required", {"basic"}}})}})}})},
     {"required", {"type", "length", "locations"}},
     {"type", "object"}});

}
#endif // LOCATIONDATABULKUPLOADSCHEMA_H
