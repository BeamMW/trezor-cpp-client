#pragma once

#include "base_device_manager.hpp"

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
    call(pack_message(message), MessageType_BeamPublicKey, callback);
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
    message.set_allocated_kidv(kidv);
    message.set_is_coin_key(isCoinKey);
    call(pack_message(message), MessageType_BeamPublicKey, callback);
    message.release_kidv();
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
    message.set_allocated_kidv(kidv);
    message.set_is_public(isPublic);
    call(pack_message(message), MessageType_BeamRangeproofData, callback);
    message.release_kidv();
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
    case MessageType_BeamPublicKey:
      execute_callback<BeamPublicKey>(call, session);
      break;
    case MessageType_BeamECCPoint:
      execute_callback<BeamECCPoint>(call, session);
      break;
    case MessageType_BeamRangeproofData:
      execute_callback<BeamRangeproofData>(call, session);
      break;
    default:
      break;
    }
  }
};