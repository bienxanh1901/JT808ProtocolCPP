#ifndef LOCATIONINFORMATIONQUERYRESPONSESCHEMA_H
#define LOCATIONINFORMATIONQUERYRESPONSESCHEMA_H

#include "LocationInformationReportSchema.h"
#include "nlohmann/json.hpp"

namespace Schema {
static nlohmann::json LocationInformationQueryResponseSchema = nlohmann::json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Location Information Query Response"},
     {"properties",
      nlohmann::json::object(
          {{"seq", nlohmann::json::object({{"description", "Message Serial Number"}, {"type", "number"}})},
           {"location", LocationInformationReportSchema}})},
     {"required", {"seq", "location"}},
     {"type", "object"}});

}
#endif // LOCATIONINFORMATIONQUERYRESPONSESCHEMA_H
