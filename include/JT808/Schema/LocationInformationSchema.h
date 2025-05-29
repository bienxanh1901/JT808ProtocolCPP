#ifndef LOCATIONINFORMATIONSCHEMA_H
#define LOCATIONINFORMATIONSCHEMA_H

#include "BasicLocationInformationSchema.h"
#include "JT808/Schema/ExtraLocationInformationSchema.h"
#include "nlohmann/json.hpp"

namespace Schema {

static nlohmann::json LocationInformationSchema =
    nlohmann::json::object({{"basic", BasicLocationInformationSchema}, {"extra", ExtraLocationInformationSchema}});
}
#endif // LOCATIONINFORMATIONSCHEMA_H
