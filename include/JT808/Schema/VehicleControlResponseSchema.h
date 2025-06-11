#ifndef VEHICLECONTROLRESPONSESCHEMA_H
#define VEHICLECONTROLRESPONSESCHEMA_H

#include "JT808/Common.h"
#include "LocationInformationSchema.h"
namespace Schema {
static Json VehicleControlResponseSchema =
    Json::object({{"$schema", "http://json-schema.org/draft-07/schema#"},
                  {"title", "Vehicle Control Response"},
                  {"properties",
                   Json::object({{"seq", Json::object({{"description", "Message Serial Number"}, {"type", "number"}})},
                                 {"location", LocationInformationSchema}})},
                  {"required", {"seq", "location"}},
                  {"type", "object"}});

}
#endif // VEHICLECONTROLRESPONSESCHEMA_H
