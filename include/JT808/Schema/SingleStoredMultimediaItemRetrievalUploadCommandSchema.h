#ifndef SINGLESTOREDMULTIMEDIAITEMRETRIEVALUPLOADCOMMANDSCHEMA_H
#define SINGLESTOREDMULTIMEDIAITEMRETRIEVALUPLOADCOMMANDSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json SingleStoredMultimediaItemRetrievalUploadCommandSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Command for Single Stored Multimedia Item Retrieval Upload ",
    "properties": {
        "id": {
            "description": "Multimedia ID",
            "type": "number"
        },
        "delete": {
            "description": "Delete Flag",
            "type": "number"
        }
    },
    "required": ["id", "delete"],
    "type": "object"
}

)"_json;

}
#endif // SINGLESTOREDMULTIMEDIAITEMRETRIEVALUPLOADCOMMANDSCHEMA_H
