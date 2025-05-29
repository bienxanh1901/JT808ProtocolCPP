#ifndef STOREDMULTIMEDIADATARETRIEVALRESPONSESCHEMA_H
#define STOREDMULTIMEDIADATARETRIEVALRESPONSESCHEMA_H

#include "MultimediaSchema.h"
#include "nlohmann/json.hpp"

namespace Schema {
static nlohmann::json StoredMultimediaDataRetrievalResponseSchema = nlohmann::json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Response to Storage Multimedia Data Retrieval"},
     {"properties",
      nlohmann::json::object(
          {{"seq", nlohmann::json::object({{"description", "Response Serial Number"}, {"type", "number"}})},
           {"length",
            nlohmann::json::object({{"description", "Total Number of Multimedia Data Items"}, {"type", "number"}})},
           {"result",
            nlohmann::json::object(
                {{"description", "Location Reporting Data Items"},
                 {"type", "array"},
                 {"items",
                  nlohmann::json::object({{"type", "object"},
                                          {"properties", MultimediaRetrievalDataSchema},
                                          {"required", {"id", "type", "channel", "event", "location"}}})}})}})},
     {"required", {"seq", "length", "result"}},
     {"type", "object"}});

}
#endif // STOREDMULTIMEDIADATARETRIEVALRESPONSESCHEMA_H
