#ifndef LOCATIONINFORMATIONQUERYRESPONSESCHEMA_H
#define LOCATIONINFORMATIONQUERYRESPONSESCHEMA_H

#include "JT808/Common.h"
#include "LocationInformationReportSchema.h"

namespace Schema {
static Json LocationInformationQueryResponseSchema =
    Json::object({{"$schema", "http://json-schema.org/draft-07/schema#"},
                  {"title", "Location Information Query Response"},
                  {"properties",
                   Json::object({{"seq", Json::object({{"description", "Message Serial Number"}, {"type", "number"}})},
                                 {"location", LocationInformationReportSchema}})},
                  {"required", {"seq", "location"}},
                  {"type", "object"}});

}
#endif // LOCATIONINFORMATIONQUERYRESPONSESCHEMA_H
