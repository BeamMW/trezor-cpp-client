#pragma once

#include <string>
#include "json.hpp"

typedef struct
{
  std::string path;
  std::string session;
} Enumerate;

inline void from_json(const nlohmann::json &j, Enumerate &value)
{
  value.path = j.at("path").get<std::string>();
  auto session = j.at("session");
  value.session = session.is_null() ? "null" : session.get<std::string>();
}
