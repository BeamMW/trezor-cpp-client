#pragma once

#include <string>
#include "json.hpp"

typedef struct
{
  std::string path;
  std::string session;
  int vendor;
  int product;
} Enumerate;

inline void from_json(const nlohmann::json &j, Enumerate &value)
{
  value.path = j.at("path").get<std::string>();
  auto session = j.at("session");
  value.session = session.is_null() ? "null" : session.get<std::string>();
  value.vendor = j.at("vendor").get<int>();
  value.product = j.at("product").get<int>();
}

namespace std
{
    inline string to_string(const Enumerate& device)
    {
        return "Trezor(device.path=" + device.path
            + ",product=" + std::to_string(device.product)
            + ",session=" + device.session
            + ",vendor=" + std::to_string(device.vendor)
            + ")";
    }
    
}
