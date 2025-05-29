#ifndef VEHICLECONTROLRESPONSESCHEMA_H
#define VEHICLECONTROLRESPONSESCHEMA_H

#include "LocationInformationSchema.h"
#include "nlohmann/json.hpp"
namespace Schema {
static nlohmann::json VehicleControlResponseSchema = nlohmann::json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Vehicle Control Response"},
     {"properties",
      nlohmann::json::object(
          {{"seq", nlohmann::json::object({{"description", "Message Serial Number"}, {"type", "number"}})},
           {"location", LocationInformationSchema}})},
     {"required", {"seq", "location"}},
     {"type", "object"}});

}
#endif // VEHICLECONTROLRESPONSESCHEMA_H
