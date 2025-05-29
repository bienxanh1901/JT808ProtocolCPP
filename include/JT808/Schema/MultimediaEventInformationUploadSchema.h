#ifndef MULTIMEDIAEVENTINFORMATIONUPLOADSCHEMA_H
#define MULTIMEDIAEVENTINFORMATIONUPLOADSCHEMA_H

#include "MultimediaSchema.h"
#include "nlohmann/json.hpp"

namespace Schema {
static nlohmann::json MultimediaEventInformationUploadSchema =
    nlohmann::json::object({{"$schema", "http://json-schema.org/draft-07/schema#"},
                            {"title", "Multimedia Event Information Upload"},
                            {"properties", MultimediaEventInformationSchema},
                            {"required", {"id", "type", "format", "event", "channel"}},
                            {"type", "object"}});

}
#endif // MULTIMEDIAEVENTINFORMATIONUPLOADSCHEMA_H
