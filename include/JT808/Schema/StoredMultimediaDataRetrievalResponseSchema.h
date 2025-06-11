#ifndef STOREDMULTIMEDIADATARETRIEVALRESPONSESCHEMA_H
#define STOREDMULTIMEDIADATARETRIEVALRESPONSESCHEMA_H

#include "JT808/Common.h"
#include "MultimediaSchema.h"

namespace Schema {
static Json StoredMultimediaDataRetrievalResponseSchema = Json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Response to Storage Multimedia Data Retrieval"},
     {"properties",
      Json::object(
          {{"seq", Json::object({{"description", "Response Serial Number"}, {"type", "number"}})},
           {"length", Json::object({{"description", "Total Number of Multimedia Data Items"}, {"type", "number"}})},
           {"result",
            Json::object({{"description", "Location Reporting Data Items"},
                          {"type", "array"},
                          {"items",
                           Json::object({{"type", "object"},
                                         {"properties", MultimediaRetrievalDataSchema},
                                         {"required", {"id", "type", "channel", "event", "location"}}})}})}})},
     {"required", {"seq", "length", "result"}},
     {"type", "object"}});

}
#endif // STOREDMULTIMEDIADATARETRIEVALRESPONSESCHEMA_H
