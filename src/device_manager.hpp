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

  void call_BeamGenerateKey(uint64_t idx, uint32_t type, uint32_t subIdx, uint64_t value, bool isCoinKey, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamGenerateKey message;
    auto kidv = message.mutable_kidv();
    kidv->set_idx(idx);
    kidv->set_type(type);
    kidv->set_sub_idx(subIdx);
    kidv->set_value(value);
    message.set_is_coin_key(isCoinKey);
    call(pack_message(message), MessageType_BeamECCPoint, callback);
  }

  void call_BeamGenerateRangeproof(uint64_t idx, uint32_t type, uint32_t subIdx, uint64_t value, bool isPublic, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamGenerateRangeproof message;
    auto kidv = message.mutable_kidv();
    kidv->set_idx(idx);
    kidv->set_type(type);
    kidv->set_sub_idx(subIdx);
    kidv->set_value(value);
    message.set_is_public(isPublic);
    call(pack_message(message), MessageType_BeamRangeproofData, callback);
  }

  void call_BeamSignTransaction(const std::vector<key_idv_t> &inputs, const std::vector<key_idv_t> &outputs, const transaction_data_t &tx_data, MessageCallback callback)
  {
    using namespace hw::trezor::messages;
    using namespace hw::trezor::messages::beam;

    BeamSignTransaction message;
    for (auto in : inputs)
    {
      auto kidv = message.add_inputs();
      kidv->set_idx(in.idx);
      kidv->set_type(in.type);
      kidv->set_sub_idx(in.sub_idx);
      kidv->set_value(in.value);
    }
    for (auto out : outputs)
    {
      auto kidv = message.add_outputs();
      kidv->set_idx(out.idx);
      kidv->set_type(out.type);
      kidv->set_sub_idx(out.sub_idx);
      kidv->set_value(out.value);
    }

    auto params = message.mutable_kernel_params();
    params->set_fee(tx_data.fee);
    params->set_min_height(tx_data.min_height);
    params->set_max_height(tx_data.max_height);

    auto commitment = params->mutable_commitment();
    commitment->set_x(tx_data.kernel_commitment.x, 32);
    commitment->set_y(tx_data.kernel_commitment.y);

    auto nonce = params->mutable_multisig_nonce();
    nonce->set_x(tx_data.kernel_nonce.x, 32);
    nonce->set_y(tx_data.kernel_nonce.y);

    message.set_offset_sk(tx_data.offset, 32);
    message.set_nonce_slot(tx_data.nonce_slot);

    call(pack_message(message), MessageType_BeamSignedTransaction, callback);
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
    default:
      break;
    }
  }
};