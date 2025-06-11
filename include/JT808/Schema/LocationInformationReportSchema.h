#ifndef LOCATIONINFORMATIONREPORTSCHEMA_H
#define LOCATIONINFORMATIONREPORTSCHEMA_H

#include "JT808/Common.h"
#include "LocationInformationSchema.h"

namespace Schema {
static Json LocationInformationReportSchema = Json::object({{"$schema", "http://json-schema.org/draft-07/schema#"},
                                                            {"title", "Location Information Report"},
                                                            {"properties", LocationInformationSchema},
                                                            {"required", {"basic"}},
                                                            {"type", "object"}});

}
#endif // LOCATIONINFORMATIONREPORTSCHEMA_H
