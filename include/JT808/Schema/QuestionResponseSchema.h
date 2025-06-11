#ifndef QUESTIONRESPONSESCHEMA_H
#define QUESTIONRESPONSESCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json QuestionResponseSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Question Response",
    "properties": {
        "seq": {
            "description": "Response Seq",
            "type": "number"
        },
        "id": {
            "description": "Answer ID",
            "type": "number"
        }
    },
    "required": ["seq", "id"],
    "type": "object"
}

)"_json;

}
#endif // QUESTIONRESPONSESCHEMA_H
