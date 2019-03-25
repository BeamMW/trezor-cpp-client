#pragma once

#include <cstdio>

extern "C" inline void hex2bin(const char *hexString, const size_t sizeString, unsigned char *outBytes)
{
  uint32_t buffer = 0;
  for (size_t i = 0; i < sizeString / 2; i++)
  {
    sscanf(hexString + 2 * i, "%2X", &buffer);
    outBytes[i] = buffer;
  }
}

template <typename T>
void copy_reversed(const uint8_t *bytes, T *value)
{
  size_t size = sizeof(T);
  for (size_t i = 0, j = size - 1; i < size; i++, j--)
    *value |= static_cast<T>(bytes[j] << i * 8);
}
