#ifndef LOCATIONINFORMATIONSCHEMA_H
#define LOCATIONINFORMATIONSCHEMA_H

#include "BasicLocationInformationSchema.h"
#include "JT808/Common.h"
#include "JT808/Schema/ExtraLocationInformationSchema.h"

namespace Schema {

static Json LocationInformationSchema =
    Json::object({{"basic", BasicLocationInformationSchema}, {"extra", ExtraLocationInformationSchema}});
}
#endif // LOCATIONINFORMATIONSCHEMA_H
