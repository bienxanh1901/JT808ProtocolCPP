#ifndef SETTINGAREASCHEMA_H
#define SETTINGAREASCHEMA_H

#include "AreaSettingPropertiesSchema.h"
#include "nlohmann/json.hpp"

namespace Schema {
static nlohmann::json CircularAreaSettingSchema = nlohmann::json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Setting Circular Area"},
     {"properties",
      nlohmann::json::object(
          {{"type", nlohmann::json::object({{"description", "Setting Attribute"}, {"type", "number"}})},
           {"length", nlohmann::json::object({{"description", "Total Number of Areas"}, {"type", "number"}})},
           {"areas",
            nlohmann::json::object(
                {{"description", "Area Item"}, {"type", "array"}, {"items", CircularAreaSchema}})}})},
     {"required", {"type", "length", "areas"}},
     {"type", "object"}});

static nlohmann::json RectangularAreaSettingSchema = nlohmann::json::object(
    {{"$schema", "http://json-schema.org/draft-07/schema#"},
     {"title", "Setting Rectangular Area"},
     {"properties",
      nlohmann::json::object(
          {{"type", nlohmann::json::object({{"description", "Setting Attribute"}, {"type", "number"}})},
           {"length", nlohmann::json::object({{"description", "Total Number of Areas"}, {"type", "number"}})},
           {"areas",
            nlohmann::json::object(
                {{"description", "Area Item"}, {"type", "array"}, {"items", RectangularAreaSchema}})}})},
     {"required", {"type", "length", "areas"}},
     {"type", "object"}});

}
#endif // SETTINGAREASCHEMA_H
