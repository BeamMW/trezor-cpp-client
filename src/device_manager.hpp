#pragma once

#include "base_device_manager.hpp"
#include "hw_definitions.hpp"

class DeviceManager: public BaseDeviceManager
{
public:
  virtual ~DeviceManager()
  {
  }

  void call_Ping(std::string text, bool button_protection, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    Ping message;
    message.set_message(text);
    message.set_button_protection(button_protection);
    call(pack_message(message), MessageType_Success, callback);
  }

  void call_BeamGetOwnerKey(bool show_display, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamGetOwnerKey message;
    message.set_show_display(show_display);
    call(pack_message(message), MessageType_BeamOwnerKey, callback);
  }

  void call_BeamGenerateNonce(uint8_t slot, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamGenerateNonce message;
    message.set_slot(slot);
    call(pack_message(message), MessageType_BeamECCPoint, callback);
  }

  void call_BeamGetNoncePublic(uint8_t slot, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamGetNoncePublic message;
    message.set_slot(slot);
    call(pack_message(message), MessageType_BeamECCPoint, callback);
  }

  // NEW CRYPTO ---------------------------------------------------------

  void call_BeamSignTransactionSend(const BeamCrypto_TxCommon &txCommon,
                                    const BeamCrypto_TxMutualInfo &txMutualInfo,
                                    const BeamCrypto_TxSenderParams txSenderParams,
                                    MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamSignTransactionSend message;

    auto tx_common = message.mutable_tx_common();
    tx_common->set_offset_sk(txCommon.m_kOffset.m_pVal, 32);
    for (auto in : *txCommon.m_pIns)
    {
      auto coinId = tx_common->add_inputs();
      coinId->set_idx(in.m_Idx);
      coinId->set_type(in.m_Type);
      coinId->set_sub_idx(in.m_SubIdx);
      coinId->set_amount(in.m_Amount);
      coinId->set_asset_id(in.m_AssetID);
    }
    for (auto out : *txCommon.m_pOuts)
    {
      auto coinId = tx_common->add_outputs();
      coinId->set_idx(out.m_Idx);
      coinId->set_type(out.m_Type);
      coinId->set_sub_idx(out.m_SubIdx);
      coinId->set_amount(out.m_Amount);
      coinId->set_asset_id(out.m_AssetID);
    }
    auto kernel_params = tx_common->mutable_kernel_params();
    kernel_params->set_fee(txCommon.m_Krn.m_Fee);
    kernel_params->set_min_height(txCommon.m_Krn.m_hMin);
    kernel_params->set_max_height(txCommon.m_Krn.m_hMax);
    auto commitment = kernel_params->mutable_commitment();
    commitment->set_x(txCommon.m_Krn.m_Commitment.m_X.m_pVal, 32);
    commitment->set_y(txCommon.m_Krn.m_Commitment.m_Y);
    auto kernel_signature = kernel_params->mutable_signature();
    kernel_signature->set_sign_k(txCommon.m_Krn.m_Signature.m_k.m_pVal, 32);
    auto kernel_nonce_pub = kernel_signature->mutable_nonce_pub();
    kernel_nonce_pub->set_x(txCommon.m_Krn.m_Signature.m_NoncePub.m_X.m_pVal, 32);
    kernel_nonce_pub->set_y(txCommon.m_Krn.m_Signature.m_NoncePub.m_Y);

    auto tx_mutual_info = message.mutable_tx_mutual_info();
    tx_mutual_info->set_peer(txMutualInfo.m_Peer.m_pVal, 32);
    tx_mutual_info->set_wallet_identity_key(txMutualInfo.m_MyIDKey);
    auto payment_proof_signature = tx_mutual_info->mutable_payment_proof_signature();
    payment_proof_signature->set_sign_k(txMutualInfo.m_PaymentProofSignature.m_k.m_pVal, 32);
    auto payment_proof_nonce_pub = payment_proof_signature->mutable_nonce_pub();
    payment_proof_nonce_pub->set_x(txMutualInfo.m_PaymentProofSignature.m_NoncePub.m_X.m_pVal, 32);
    payment_proof_nonce_pub->set_y(txMutualInfo.m_PaymentProofSignature.m_NoncePub.m_Y);

    message.set_nonce_slot(txSenderParams.m_iSlot);
    message.set_user_agreement(txSenderParams.m_UserAgreement.m_pVal, 32);

    call(pack_message(message), MessageType_BeamSignTransactionSend, callback);
  }

  void call_BeamSignTransactionReceive(const BeamCrypto_TxCommon &txCommon,
                                       const BeamCrypto_TxMutualInfo &txMutualInfo,
                                       MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamSignTransactionReceive message;

    auto tx_common = message.mutable_tx_common();
    tx_common->set_offset_sk(txCommon.m_kOffset.m_pVal, 32);
    for (auto in : *txCommon.m_pIns)
    {
      auto coinId = tx_common->add_inputs();
      coinId->set_idx(in.m_Idx);
      coinId->set_type(in.m_Type);
      coinId->set_sub_idx(in.m_SubIdx);
      coinId->set_amount(in.m_Amount);
      coinId->set_asset_id(in.m_AssetID);
    }
    for (auto out : *txCommon.m_pOuts)
    {
      auto coinId = tx_common->add_outputs();
      coinId->set_idx(out.m_Idx);
      coinId->set_type(out.m_Type);
      coinId->set_sub_idx(out.m_SubIdx);
      coinId->set_amount(out.m_Amount);
      coinId->set_asset_id(out.m_AssetID);
    }
    auto kernel_params = tx_common->mutable_kernel_params();
    kernel_params->set_fee(txCommon.m_Krn.m_Fee);
    kernel_params->set_min_height(txCommon.m_Krn.m_hMin);
    kernel_params->set_max_height(txCommon.m_Krn.m_hMax);
    auto commitment = kernel_params->mutable_commitment();
    commitment->set_x(txCommon.m_Krn.m_Commitment.m_X.m_pVal, 32);
    commitment->set_y(txCommon.m_Krn.m_Commitment.m_Y);
    auto kernel_signature = kernel_params->mutable_signature();
    kernel_signature->set_sign_k(txCommon.m_Krn.m_Signature.m_k.m_pVal, 32);
    auto kernel_nonce_pub = kernel_signature->mutable_nonce_pub();
    kernel_nonce_pub->set_x(txCommon.m_Krn.m_Signature.m_NoncePub.m_X.m_pVal, 32);
    kernel_nonce_pub->set_y(txCommon.m_Krn.m_Signature.m_NoncePub.m_Y);

    auto tx_mutual_info = message.mutable_tx_mutual_info();
    tx_mutual_info->set_peer(txMutualInfo.m_Peer.m_pVal, 32);
    tx_mutual_info->set_wallet_identity_key(txMutualInfo.m_MyIDKey);
    auto payment_proof_signature = tx_mutual_info->mutable_payment_proof_signature();
    payment_proof_signature->set_sign_k(txMutualInfo.m_PaymentProofSignature.m_k.m_pVal, 32);
    auto payment_proof_nonce_pub = payment_proof_signature->mutable_nonce_pub();
    payment_proof_nonce_pub->set_x(txMutualInfo.m_PaymentProofSignature.m_NoncePub.m_X.m_pVal, 32);
    payment_proof_nonce_pub->set_y(txMutualInfo.m_PaymentProofSignature.m_NoncePub.m_Y);

    call(pack_message(message), MessageType_BeamSignTransactionReceive, callback);
  }

  void call_BeamSignTransactionSplit(const BeamCrypto_TxCommon &txCommon,
                                     MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamSignTransactionSplit message;

    auto tx_common = message.mutable_tx_common();
    tx_common->set_offset_sk(txCommon.m_kOffset.m_pVal, 32);
    for (auto in : *txCommon.m_pIns)
    {
      auto coinId = tx_common->add_inputs();
      coinId->set_idx(in.m_Idx);
      coinId->set_type(in.m_Type);
      coinId->set_sub_idx(in.m_SubIdx);
      coinId->set_amount(in.m_Amount);
      coinId->set_asset_id(in.m_AssetID);
    }
    for (auto out : *txCommon.m_pOuts)
    {
      auto coinId = tx_common->add_outputs();
      coinId->set_idx(out.m_Idx);
      coinId->set_type(out.m_Type);
      coinId->set_sub_idx(out.m_SubIdx);
      coinId->set_amount(out.m_Amount);
      coinId->set_asset_id(out.m_AssetID);
    }
    auto kernel_params = tx_common->mutable_kernel_params();
    kernel_params->set_fee(txCommon.m_Krn.m_Fee);
    kernel_params->set_min_height(txCommon.m_Krn.m_hMin);
    kernel_params->set_max_height(txCommon.m_Krn.m_hMax);
    auto commitment = kernel_params->mutable_commitment();
    commitment->set_x(txCommon.m_Krn.m_Commitment.m_X.m_pVal, 32);
    commitment->set_y(txCommon.m_Krn.m_Commitment.m_Y);
    auto kernel_signature = kernel_params->mutable_signature();
    kernel_signature->set_sign_k(txCommon.m_Krn.m_Signature.m_k.m_pVal, 32);
    auto kernel_nonce_pub = kernel_signature->mutable_nonce_pub();
    kernel_nonce_pub->set_x(txCommon.m_Krn.m_Signature.m_NoncePub.m_X.m_pVal, 32);
    kernel_nonce_pub->set_y(txCommon.m_Krn.m_Signature.m_NoncePub.m_Y);

    call(pack_message(message), MessageType_BeamSignTransactionSplit, callback);
  }

protected:
  virtual void handle_custom_response(const Call &call, const std::string &session)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    switch (call.type)
    {
    case MessageType_BeamOwnerKey:
      execute_callback<BeamOwnerKey>(call, session);
      break;
    case MessageType_BeamECCPoint:
      execute_callback<BeamECCPoint>(call, session);
      break;
    case MessageType_BeamRangeproofData:
      execute_callback<BeamRangeproofData>(call, session);
      break;
    case MessageType_BeamSignedTransaction:
      execute_callback<BeamSignedTransaction>(call, session);
      break;
    case MessageType_BeamSignTransactionSend:
      execute_callback<BeamSignTransactionSend>(call, session);
      break;
    case MessageType_BeamSignTransactionReceive:
      execute_callback<BeamSignTransactionReceive>(call, session);
      break;
    case MessageType_BeamSignTransactionSplit:
      execute_callback<BeamSignTransactionSplit>(call, session);
      break;
    default:
      break;
    }
  }
};