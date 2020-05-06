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

typedef uint8_t scalar_packed_t[32];

typedef struct
{
  struct
  {
    point_t a;
    point_t s;
  } part1;

  struct
  {
    point_t t1;
    point_t t2;
  } part2;

  struct
  {
    scalar_packed_t tauX;
  } part3;

  struct
  {
    point_t LR[INNER_PRODUCT_N_CYCLES][2];
    scalar_packed_t condensed[2];
  } p_tag;

  scalar_packed_t mu;
  scalar_packed_t tDot;
} rangeproof_confidential_packed_t;

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

// NEW CRYPTO ---------------------------------------------------------

#define BeamCrypto_nBytes 32UL

typedef uint64_t BeamCrypto_Amount;
typedef uint32_t BeamCrypto_AssetID;
typedef uint64_t BeamCrypto_Height;
typedef uint64_t BeamCrypto_WalletIdentity;

typedef struct
{
  uint8_t m_pVal[BeamCrypto_nBytes];
} BeamCrypto_UintBig;

typedef struct
{
  // platform-independent EC point representation
  BeamCrypto_UintBig m_X;
  uint8_t m_Y;
} BeamCrypto_CompactPoint;

typedef struct
{
  uint64_t m_Idx;
  uint32_t m_Type;
  uint32_t m_SubIdx;

  BeamCrypto_Amount m_Amount;
  BeamCrypto_AssetID m_AssetID;

} BeamCrypto_CoinID;

typedef struct
{
  BeamCrypto_CompactPoint m_NoncePub;
  BeamCrypto_UintBig m_k; // scalar, but in a platform-independent way

} BeamCrypto_Signature; // Schnorr

typedef struct
{
  BeamCrypto_Amount m_Fee;
  BeamCrypto_Height m_hMin;
  BeamCrypto_Height m_hMax;

  BeamCrypto_CompactPoint m_Commitment;
  BeamCrypto_Signature m_Signature;

} BeamCrypto_TxKernel;

typedef struct
{
  const std::vector<BeamCrypto_CoinID> *m_pIns;
  const std::vector<BeamCrypto_CoinID> *m_pOuts;

  BeamCrypto_TxKernel m_Krn;
  BeamCrypto_UintBig m_kOffset;

} BeamCrypto_TxCommon;

typedef struct
{
  BeamCrypto_UintBig m_Peer;
  BeamCrypto_WalletIdentity m_MyIDKey;
  BeamCrypto_Signature m_PaymentProofSignature;

} BeamCrypto_TxMutualInfo;

typedef struct
{
  uint32_t m_iSlot;
  BeamCrypto_UintBig m_UserAgreement; // set to Zero on 1st invocation

} BeamCrypto_TxSenderParams;
