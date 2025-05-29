#ifndef LOCATIONINFORMATIONREPORTSCHEMA_H
#define LOCATIONINFORMATIONREPORTSCHEMA_H

#include "LocationInformationSchema.h"
#include "nlohmann/json.hpp"

namespace Schema {
static nlohmann::json LocationInformationReportSchema =
    nlohmann::json::object({{"$schema", "http://json-schema.org/draft-07/schema#"},
                            {"title", "Location Information Report"},
                            {"properties", LocationInformationSchema},
                            {"required", {"basic"}},
                            {"type", "object"}});

}
#endif // LOCATIONINFORMATIONREPORTSCHEMA_H
