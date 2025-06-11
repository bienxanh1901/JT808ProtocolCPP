#ifndef SETTINGAREASCHEMA_H
#define SETTINGAREASCHEMA_H

#include "AreaSettingPropertiesSchema.h"
#include "JT808/Common.h"

namespace Schema {
static Json CircularAreaSettingSchema = Json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Setting Circular Area"},
     {"properties",
      Json::object(
          {{"type", Json::object({{"description", "Setting Attribute"}, {"type", "number"}})},
           {"length", Json::object({{"description", "Total Number of Areas"}, {"type", "number"}})},
           {"areas", Json::object({{"description", "Area Item"}, {"type", "array"}, {"items", CircularAreaSchema}})}})},
     {"required", {"type", "length", "areas"}},
     {"type", "object"}});

static Json RectangularAreaSettingSchema = Json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Setting Rectangular Area"},
     {"properties",
      Json::object(
          {{"type", Json::object({{"description", "Setting Attribute"}, {"type", "number"}})},
           {"length", Json::object({{"description", "Total Number of Areas"}, {"type", "number"}})},
           {"areas",
            Json::object({{"description", "Area Item"}, {"type", "array"}, {"items", RectangularAreaSchema}})}})},
     {"required", {"type", "length", "areas"}},
     {"type", "object"}});

}
#endif // SETTINGAREASCHEMA_H
