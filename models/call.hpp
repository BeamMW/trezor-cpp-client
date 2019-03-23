#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>
#include "utils.hpp"

typedef struct
{
  uint16_t type = 0;
  uint32_t length = 0;
  std::vector<uint8_t> msg;
} Call;

inline void from_bytes(const uint8_t *bytes, Call &value)
{
  copy_reversed(bytes, &value.type);
  copy_reversed(bytes + sizeof(value.type), &value.length);
  std::copy_n(bytes + sizeof(value.type) + sizeof(value.length),
              value.length, std::back_inserter(value.msg));
}
