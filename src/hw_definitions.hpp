#pragma once

#include <stdint.h>

#define DIGEST_LENGTH           32
#define INNER_PRODUCT_N_CYCLES  6U

typedef struct
{
  uint8_t x[DIGEST_LENGTH];
  uint8_t y;
} point_t;

typedef struct
{
  uint32_t d[8];
} scalar_t;

typedef struct
{
  point_t LR[INNER_PRODUCT_N_CYCLES][2];
  scalar_t condensed[2];
} inner_product_t;

typedef struct
{
  // Bulletproof scheme

  struct Part1
  {
    point_t a;
    point_t s;
  } part1;

  // <- y,z

  struct Part2
  {
    point_t t1;
    point_t t2;
  } part2;

  // <- x

  struct Part3
  {
    scalar_t tauX;
  } part3;

  scalar_t mu;
  scalar_t tDot;
  inner_product_t p_tag;
} rangeproof_confidential_t;

typedef struct
{
  uint64_t idx;
  uint32_t type;
  uint32_t sub_idx;
  uint64_t value;
} key_idv_t;

typedef struct
{
  // Common kernel parameters
  uint64_t fee;
  uint64_t min_height;
  uint64_t max_height;

  // Aggregated data
  point_t kernel_commitment;
  point_t kernel_nonce;

  // Nonce slot used
  uint32_t nonce_slot;

  // Additional explicit blinding factor that should be added
  uint8_t offset[32];
} transaction_data_t;
