#ifndef QUESTIONDISPATCHSCHEMA_H
#define QUESTIONDISPATCHSCHEMA_H

#include "JT808/Common.h"
namespace Schema {
static Json QuestionDispatchSchema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Question Dispatch",
    "properties": {
        "flag": {
            "description": "Flag",
            "type": "number"
        },
        "length": {
            "description": "Number answers",
            "type": "number"
        },
        "question": {
            "description": "Question",
            "type": "string"

        },
        "answers": {
            "description": "Answer Candidate List",
            "type": "array",
            "items": {
                "type": "object",
                "properties": {
                    "id": {
                        "description": "Answer ID",
                        "type": "number"
                    },
                    "answer": {
                        "description": "Answer Content",
                        "type": "string"
                    }
                },
                "required": ["id", "answer"]
            }
        }
    },
    "required": ["flag", "question", "length", "answers"],
    "type": "object"
}

)"_json;

}
#endif // QUESTIONDISPATCHSCHEMA_H
