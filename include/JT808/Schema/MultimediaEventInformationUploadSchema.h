#ifndef MULTIMEDIAEVENTINFORMATIONUPLOADSCHEMA_H
#define MULTIMEDIAEVENTINFORMATIONUPLOADSCHEMA_H

#include "JT808/Common.h"
#include "MultimediaSchema.h"

namespace Schema {
static Json MultimediaEventInformationUploadSchema =
    Json::object({{"$schema", "http://json-schema.org/draft-07/schema#"},
                  {"title", "Multimedia Event Information Upload"},
                  {"properties", MultimediaEventInformationSchema},
                  {"required", {"id", "type", "format", "event", "channel"}},
                  {"type", "object"}});

}
#endif // MULTIMEDIAEVENTINFORMATIONUPLOADSCHEMA_H
