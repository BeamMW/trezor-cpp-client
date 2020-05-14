// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: messages.proto

#include "messages.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

namespace hw {
namespace trezor {
namespace messages {
}  // namespace messages
}  // namespace trezor
}  // namespace hw
void InitDefaults_messages_2eproto() {
}

constexpr ::google::protobuf::Metadata* file_level_metadata_messages_2eproto = nullptr;
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors_messages_2eproto[1];
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_messages_2eproto = nullptr;
const ::google::protobuf::uint32 TableStruct_messages_2eproto::offsets[1] = {};
static constexpr ::google::protobuf::internal::MigrationSchema* schemas = nullptr;
static constexpr ::google::protobuf::Message* const* file_default_instances = nullptr;

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_messages_2eproto = {
  {}, AddDescriptors_messages_2eproto, "messages.proto", schemas,
  file_default_instances, TableStruct_messages_2eproto::offsets,
  file_level_metadata_messages_2eproto, 0, file_level_enum_descriptors_messages_2eproto, file_level_service_descriptors_messages_2eproto,
};

const char descriptor_table_protodef_messages_2eproto[] =
  "\n\016messages.proto\022\022hw.trezor.messages\032 go"
  "ogle/protobuf/descriptor.proto*\211E\n\013Messa"
  "geType\022$\n\026MessageType_Initialize\020\000\032\010\220\265\030\001"
  "\260\265\030\001\022\032\n\020MessageType_Ping\020\001\032\004\220\265\030\001\022\035\n\023Mess"
  "ageType_Success\020\002\032\004\230\265\030\001\022\035\n\023MessageType_F"
  "ailure\020\003\032\004\230\265\030\001\022\037\n\025MessageType_ChangePin\020"
  "\004\032\004\220\265\030\001\022 \n\026MessageType_WipeDevice\020\005\032\004\220\265\030"
  "\001\022 \n\026MessageType_GetEntropy\020\t\032\004\220\265\030\001\022\035\n\023M"
  "essageType_Entropy\020\n\032\004\230\265\030\001\022 \n\026MessageTyp"
  "e_LoadDevice\020\r\032\004\220\265\030\001\022!\n\027MessageType_Rese"
  "tDevice\020\016\032\004\220\265\030\001\022\036\n\024MessageType_Features\020"
  "\021\032\004\230\265\030\001\022&\n\034MessageType_PinMatrixRequest\020"
  "\022\032\004\230\265\030\001\022*\n\030MessageType_PinMatrixAck\020\023\032\014\220"
  "\265\030\001\260\265\030\001\300\265\030\001\022 \n\022MessageType_Cancel\020\024\032\010\220\265\030"
  "\001\260\265\030\001\022\"\n\030MessageType_ClearSession\020\030\032\004\220\265\030"
  "\001\022#\n\031MessageType_ApplySettings\020\031\032\004\220\265\030\001\022#"
  "\n\031MessageType_ButtonRequest\020\032\032\004\230\265\030\001\022\'\n\025M"
  "essageType_ButtonAck\020\033\032\014\220\265\030\001\260\265\030\001\300\265\030\001\022 \n\026"
  "MessageType_ApplyFlags\020\034\032\004\220\265\030\001\022\"\n\030Messag"
  "eType_BackupDevice\020\"\032\004\220\265\030\001\022$\n\032MessageTyp"
  "e_EntropyRequest\020#\032\004\230\265\030\001\022 \n\026MessageType_"
  "EntropyAck\020$\032\004\220\265\030\001\022\'\n\035MessageType_Passph"
  "raseRequest\020)\032\004\230\265\030\001\022+\n\031MessageType_Passp"
  "hraseAck\020*\032\014\220\265\030\001\260\265\030\001\300\265\030\001\022,\n\"MessageType_"
  "PassphraseStateRequest\020M\032\004\230\265\030\001\0220\n\036Messag"
  "eType_PassphraseStateAck\020N\032\014\220\265\030\001\260\265\030\001\300\265\030\001"
  "\022$\n\032MessageType_RecoveryDevice\020-\032\004\220\265\030\001\022!"
  "\n\027MessageType_WordRequest\020.\032\004\230\265\030\001\022\035\n\023Mes"
  "sageType_WordAck\020/\032\004\220\265\030\001\022!\n\027MessageType_"
  "GetFeatures\0207\032\004\220\265\030\001\022#\n\031MessageType_SetU2"
  "FCounter\020\?\032\004\220\265\030\001\022\037\n\025MessageType_SdProtec"
  "t\020O\032\004\220\265\030\001\022\'\n\035MessageType_GetNextU2FCount"
  "er\020P\032\004\220\265\030\001\022$\n\032MessageType_NextU2FCounter"
  "\020Q\032\004\230\265\030\001\022$\n\032MessageType_ChangeWipeCode\020R"
  "\032\004\220\265\030\001\022\'\n\031MessageType_FirmwareErase\020\006\032\010\220"
  "\265\030\001\270\265\030\001\022(\n\032MessageType_FirmwareUpload\020\007\032"
  "\010\220\265\030\001\270\265\030\001\022)\n\033MessageType_FirmwareRequest"
  "\020\010\032\010\230\265\030\001\270\265\030\001\022\"\n\024MessageType_SelfTest\020 \032\010"
  "\220\265\030\001\270\265\030\001\022\"\n\030MessageType_GetPublicKey\020\013\032\004"
  "\220\265\030\001\022\037\n\025MessageType_PublicKey\020\014\032\004\230\265\030\001\022\034\n"
  "\022MessageType_SignTx\020\017\032\004\220\265\030\001\022\037\n\025MessageTy"
  "pe_TxRequest\020\025\032\004\230\265\030\001\022\033\n\021MessageType_TxAc"
  "k\020\026\032\004\220\265\030\001\022 \n\026MessageType_GetAddress\020\035\032\004\220"
  "\265\030\001\022\035\n\023MessageType_Address\020\036\032\004\230\265\030\001\022!\n\027Me"
  "ssageType_SignMessage\020&\032\004\220\265\030\001\022#\n\031Message"
  "Type_VerifyMessage\020\'\032\004\220\265\030\001\022&\n\034MessageTyp"
  "e_MessageSignature\020(\032\004\230\265\030\001\022$\n\032MessageTyp"
  "e_CipherKeyValue\020\027\032\004\220\265\030\001\022&\n\034MessageType_"
  "CipheredKeyValue\0200\032\004\230\265\030\001\022\"\n\030MessageType_"
  "SignIdentity\0205\032\004\220\265\030\001\022$\n\032MessageType_Sign"
  "edIdentity\0206\032\004\230\265\030\001\022\'\n\035MessageType_GetECD"
  "HSessionKey\020=\032\004\220\265\030\001\022$\n\032MessageType_ECDHS"
  "essionKey\020>\032\004\230\265\030\001\022 \n\026MessageType_CosiCom"
  "mit\020G\032\004\220\265\030\001\022$\n\032MessageType_CosiCommitmen"
  "t\020H\032\004\230\265\030\001\022\036\n\024MessageType_CosiSign\020I\032\004\220\265\030"
  "\001\022#\n\031MessageType_CosiSignature\020J\032\004\230\265\030\001\022/"
  "\n\035MessageType_DebugLinkDecision\020d\032\014\240\265\030\001\260"
  "\265\030\001\300\265\030\001\022+\n\035MessageType_DebugLinkGetState"
  "\020e\032\010\240\265\030\001\260\265\030\001\022$\n\032MessageType_DebugLinkSta"
  "te\020f\032\004\250\265\030\001\022#\n\031MessageType_DebugLinkStop\020"
  "g\032\004\240\265\030\001\022\"\n\030MessageType_DebugLinkLog\020h\032\004\250"
  "\265\030\001\022)\n\037MessageType_DebugLinkMemoryRead\020n"
  "\032\004\240\265\030\001\022%\n\033MessageType_DebugLinkMemory\020o\032"
  "\004\250\265\030\001\022*\n MessageType_DebugLinkMemoryWrit"
  "e\020p\032\004\240\265\030\001\022)\n\037MessageType_DebugLinkFlashE"
  "rase\020q\032\004\240\265\030\001\022&\n\033MessageType_DebugLinkLay"
  "out\020\251F\032\004\250\265\030\001\022+\n MessageType_EthereumGetP"
  "ublicKey\020\302\003\032\004\220\265\030\001\022(\n\035MessageType_Ethereu"
  "mPublicKey\020\303\003\032\004\230\265\030\001\022(\n\036MessageType_Ether"
  "eumGetAddress\0208\032\004\220\265\030\001\022%\n\033MessageType_Eth"
  "ereumAddress\0209\032\004\230\265\030\001\022$\n\032MessageType_Ethe"
  "reumSignTx\020:\032\004\220\265\030\001\022\'\n\035MessageType_Ethere"
  "umTxRequest\020;\032\004\230\265\030\001\022#\n\031MessageType_Ether"
  "eumTxAck\020<\032\004\220\265\030\001\022)\n\037MessageType_Ethereum"
  "SignMessage\020@\032\004\220\265\030\001\022+\n!MessageType_Ether"
  "eumVerifyMessage\020A\032\004\220\265\030\001\022.\n$MessageType_"
  "EthereumMessageSignature\020B\032\004\230\265\030\001\022#\n\031Mess"
  "ageType_NEMGetAddress\020C\032\004\220\265\030\001\022 \n\026Message"
  "Type_NEMAddress\020D\032\004\230\265\030\001\022\037\n\025MessageType_N"
  "EMSignTx\020E\032\004\220\265\030\001\022!\n\027MessageType_NEMSigne"
  "dTx\020F\032\004\230\265\030\001\022\'\n\035MessageType_NEMDecryptMes"
  "sage\020K\032\004\220\265\030\001\022)\n\037MessageType_NEMDecrypted"
  "Message\020L\032\004\230\265\030\001\022$\n\032MessageType_LiskGetAd"
  "dress\020r\032\004\220\265\030\001\022!\n\027MessageType_LiskAddress"
  "\020s\032\004\230\265\030\001\022 \n\026MessageType_LiskSignTx\020t\032\004\220\265"
  "\030\001\022\"\n\030MessageType_LiskSignedTx\020u\032\004\230\265\030\001\022%"
  "\n\033MessageType_LiskSignMessage\020v\032\004\220\265\030\001\022*\n"
  " MessageType_LiskMessageSignature\020w\032\004\230\265\030"
  "\001\022\'\n\035MessageType_LiskVerifyMessage\020x\032\004\220\265"
  "\030\001\022&\n\034MessageType_LiskGetPublicKey\020y\032\004\220\265"
  "\030\001\022#\n\031MessageType_LiskPublicKey\020z\032\004\230\265\030\001\022"
  "&\n\033MessageType_TezosGetAddress\020\226\001\032\004\220\265\030\001\022"
  "#\n\030MessageType_TezosAddress\020\227\001\032\004\230\265\030\001\022\"\n\027"
  "MessageType_TezosSignTx\020\230\001\032\004\220\265\030\001\022$\n\031Mess"
  "ageType_TezosSignedTx\020\231\001\032\004\230\265\030\001\022(\n\035Messag"
  "eType_TezosGetPublicKey\020\232\001\032\004\220\265\030\001\022%\n\032Mess"
  "ageType_TezosPublicKey\020\233\001\032\004\230\265\030\001\022$\n\031Messa"
  "geType_StellarSignTx\020\312\001\032\004\220\265\030\001\022)\n\036Message"
  "Type_StellarTxOpRequest\020\313\001\032\004\230\265\030\001\022(\n\035Mess"
  "ageType_StellarGetAddress\020\317\001\032\004\220\265\030\001\022%\n\032Me"
  "ssageType_StellarAddress\020\320\001\032\004\230\265\030\001\022-\n\"Mes"
  "sageType_StellarCreateAccountOp\020\322\001\032\004\220\265\030\001"
  "\022\'\n\034MessageType_StellarPaymentOp\020\323\001\032\004\220\265\030"
  "\001\022+\n MessageType_StellarPathPaymentOp\020\324\001"
  "\032\004\220\265\030\001\022+\n MessageType_StellarManageOffer"
  "Op\020\325\001\032\004\220\265\030\001\0222\n\'MessageType_StellarCreate"
  "PassiveOfferOp\020\326\001\032\004\220\265\030\001\022*\n\037MessageType_S"
  "tellarSetOptionsOp\020\327\001\032\004\220\265\030\001\022+\n MessageTy"
  "pe_StellarChangeTrustOp\020\330\001\032\004\220\265\030\001\022*\n\037Mess"
  "ageType_StellarAllowTrustOp\020\331\001\032\004\220\265\030\001\022,\n!"
  "MessageType_StellarAccountMergeOp\020\332\001\032\004\220\265"
  "\030\001\022*\n\037MessageType_StellarManageDataOp\020\334\001"
  "\032\004\220\265\030\001\022,\n!MessageType_StellarBumpSequenc"
  "eOp\020\335\001\032\004\220\265\030\001\022&\n\033MessageType_StellarSigne"
  "dTx\020\346\001\032\004\230\265\030\001\022$\n\031MessageType_CardanoSignT"
  "x\020\257\002\032\004\220\265\030\001\022\'\n\034MessageType_CardanoTxReque"
  "st\020\260\002\032\004\230\265\030\001\022*\n\037MessageType_CardanoGetPub"
  "licKey\020\261\002\032\004\220\265\030\001\022\'\n\034MessageType_CardanoPu"
  "blicKey\020\262\002\032\004\230\265\030\001\022(\n\035MessageType_CardanoG"
  "etAddress\020\263\002\032\004\220\265\030\001\022%\n\032MessageType_Cardan"
  "oAddress\020\264\002\032\004\230\265\030\001\022#\n\030MessageType_Cardano"
  "TxAck\020\265\002\032\004\220\265\030\001\022&\n\033MessageType_CardanoSig"
  "nedTx\020\266\002\032\004\230\265\030\001\022\'\n\034MessageType_RippleGetA"
  "ddress\020\220\003\032\004\220\265\030\001\022$\n\031MessageType_RippleAdd"
  "ress\020\221\003\032\004\230\265\030\001\022#\n\030MessageType_RippleSignT"
  "x\020\222\003\032\004\220\265\030\001\022%\n\032MessageType_RippleSignedTx"
  "\020\223\003\032\004\220\265\030\001\0223\n(MessageType_MoneroTransacti"
  "onInitRequest\020\365\003\032\004\230\265\030\001\022/\n$MessageType_Mo"
  "neroTransactionInitAck\020\366\003\032\004\230\265\030\001\0227\n,Messa"
  "geType_MoneroTransactionSetInputRequest\020"
  "\367\003\032\004\230\265\030\001\0223\n(MessageType_MoneroTransactio"
  "nSetInputAck\020\370\003\032\004\230\265\030\001\022@\n5MessageType_Mon"
  "eroTransactionInputsPermutationRequest\020\371"
  "\003\032\004\230\265\030\001\022<\n1MessageType_MoneroTransaction"
  "InputsPermutationAck\020\372\003\032\004\230\265\030\001\0228\n-Message"
  "Type_MoneroTransactionInputViniRequest\020\373"
  "\003\032\004\230\265\030\001\0224\n)MessageType_MoneroTransaction"
  "InputViniAck\020\374\003\032\004\230\265\030\001\022;\n0MessageType_Mon"
  "eroTransactionAllInputsSetRequest\020\375\003\032\004\230\265"
  "\030\001\0227\n,MessageType_MoneroTransactionAllIn"
  "putsSetAck\020\376\003\032\004\230\265\030\001\0228\n-MessageType_Moner"
  "oTransactionSetOutputRequest\020\377\003\032\004\230\265\030\001\0224\n"
  ")MessageType_MoneroTransactionSetOutputA"
  "ck\020\200\004\032\004\230\265\030\001\0228\n-MessageType_MoneroTransac"
  "tionAllOutSetRequest\020\201\004\032\004\230\265\030\001\0224\n)Message"
  "Type_MoneroTransactionAllOutSetAck\020\202\004\032\004\230"
  "\265\030\001\0228\n-MessageType_MoneroTransactionSign"
  "InputRequest\020\203\004\032\004\230\265\030\001\0224\n)MessageType_Mon"
  "eroTransactionSignInputAck\020\204\004\032\004\230\265\030\001\0224\n)M"
  "essageType_MoneroTransactionFinalRequest"
  "\020\205\004\032\004\230\265\030\001\0220\n%MessageType_MoneroTransacti"
  "onFinalAck\020\206\004\032\004\230\265\030\001\0226\n+MessageType_Moner"
  "oKeyImageExportInitRequest\020\222\004\032\004\230\265\030\001\0222\n\'M"
  "essageType_MoneroKeyImageExportInitAck\020\223"
  "\004\032\004\230\265\030\001\0224\n)MessageType_MoneroKeyImageSyn"
  "cStepRequest\020\224\004\032\004\230\265\030\001\0220\n%MessageType_Mon"
  "eroKeyImageSyncStepAck\020\225\004\032\004\230\265\030\001\0225\n*Messa"
  "geType_MoneroKeyImageSyncFinalRequest\020\226\004"
  "\032\004\230\265\030\001\0221\n&MessageType_MoneroKeyImageSync"
  "FinalAck\020\227\004\032\004\230\265\030\001\022\'\n\034MessageType_MoneroG"
  "etAddress\020\234\004\032\004\220\265\030\001\022$\n\031MessageType_Monero"
  "Address\020\235\004\032\004\230\265\030\001\022(\n\035MessageType_MoneroGe"
  "tWatchKey\020\236\004\032\004\220\265\030\001\022%\n\032MessageType_Monero"
  "WatchKey\020\237\004\032\004\230\265\030\001\022-\n\"MessageType_DebugMo"
  "neroDiagRequest\020\242\004\032\004\220\265\030\001\022)\n\036MessageType_"
  "DebugMoneroDiagAck\020\243\004\032\004\230\265\030\001\022,\n!MessageTy"
  "pe_MoneroGetTxKeyRequest\020\246\004\032\004\220\265\030\001\022(\n\035Mes"
  "sageType_MoneroGetTxKeyAck\020\247\004\032\004\230\265\030\001\0224\n)M"
  "essageType_MoneroLiveRefreshStartRequest"
  "\020\250\004\032\004\220\265\030\001\0220\n%MessageType_MoneroLiveRefre"
  "shStartAck\020\251\004\032\004\230\265\030\001\0223\n(MessageType_Moner"
  "oLiveRefreshStepRequest\020\252\004\032\004\220\265\030\001\022/\n$Mess"
  "ageType_MoneroLiveRefreshStepAck\020\253\004\032\004\230\265\030"
  "\001\0224\n)MessageType_MoneroLiveRefreshFinalR"
  "equest\020\254\004\032\004\220\265\030\001\0220\n%MessageType_MoneroLiv"
  "eRefreshFinalAck\020\255\004\032\004\230\265\030\001\022&\n\033MessageType"
  "_EosGetPublicKey\020\330\004\032\004\220\265\030\001\022#\n\030MessageType"
  "_EosPublicKey\020\331\004\032\004\230\265\030\001\022 \n\025MessageType_Eo"
  "sSignTx\020\332\004\032\004\220\265\030\001\022)\n\036MessageType_EosTxAct"
  "ionRequest\020\333\004\032\004\230\265\030\001\022%\n\032MessageType_EosTx"
  "ActionAck\020\334\004\032\004\220\265\030\001\022\"\n\027MessageType_EosSig"
  "nedTx\020\335\004\032\004\230\265\030\001\022(\n\035MessageType_BinanceGet"
  "Address\020\274\005\032\004\220\265\030\001\022%\n\032MessageType_BinanceA"
  "ddress\020\275\005\032\004\230\265\030\001\022*\n\037MessageType_BinanceGe"
  "tPublicKey\020\276\005\032\004\220\265\030\001\022\'\n\034MessageType_Binan"
  "cePublicKey\020\277\005\032\004\230\265\030\001\022$\n\031MessageType_Bina"
  "nceSignTx\020\300\005\032\004\220\265\030\001\022\'\n\034MessageType_Binanc"
  "eTxRequest\020\301\005\032\004\230\265\030\001\022)\n\036MessageType_Binan"
  "ceTransferMsg\020\302\005\032\004\220\265\030\001\022&\n\033MessageType_Bi"
  "nanceOrderMsg\020\303\005\032\004\220\265\030\001\022\'\n\034MessageType_Bi"
  "nanceCancelMsg\020\304\005\032\004\220\265\030\001\022&\n\033MessageType_B"
  "inanceSignedTx\020\305\005\032\004\230\265\030\001\0226\n+MessageType_W"
  "ebAuthnListResidentCredentials\020\240\006\032\004\220\265\030\001\022"
  "*\n\037MessageType_WebAuthnCredentials\020\241\006\032\004\230"
  "\265\030\001\0224\n)MessageType_WebAuthnAddResidentCr"
  "edential\020\242\006\032\004\220\265\030\001\0227\n,MessageType_WebAuth"
  "nRemoveResidentCredential\020\243\006\032\004\220\265\030\001\022&\n\033Me"
  "ssageType_BeamSignMessage\020\206\007\032\004\220\265\030\001\022$\n\031Me"
  "ssageType_BeamSignature\020\207\007\032\004\230\265\030\001\022(\n\035Mess"
  "ageType_BeamVerifyMessage\020\210\007\032\004\220\265\030\001\022\'\n\034Me"
  "ssageType_BeamGetPublicKey\020\211\007\032\004\220\265\030\001\022&\n\033M"
  "essageType_BeamGetOwnerKey\020\213\007\032\004\220\265\030\001\022#\n\030M"
  "essageType_BeamOwnerKey\020\214\007\032\004\230\265\030\001\022&\n\033Mess"
  "ageType_BeamGenerateKey\020\215\007\032\004\220\265\030\001\022(\n\035Mess"
  "ageType_BeamGenerateNonce\020\216\007\032\004\220\265\030\001\022#\n\030Me"
  "ssageType_BeamECCPoint\020\217\007\032\004\230\265\030\001\022-\n\"Messa"
  "geType_BeamGenerateRangeproof\020\220\007\032\004\220\265\030\001\022)"
  "\n\036MessageType_BeamRangeproofData\020\221\007\032\004\230\265\030"
  "\001\022*\n\037MessageType_BeamSignTransaction\020\222\007\032"
  "\004\220\265\030\001\022,\n!MessageType_BeamSignedTransacti"
  "on\020\223\007\032\004\230\265\030\001\022)\n\036MessageType_BeamGetNonceP"
  "ublic\020\224\007\032\004\220\265\030\001\022.\n#MessageType_BeamSignTr"
  "ansactionSend\020\225\007\032\004\220\265\030\001\0224\n)MessageType_Be"
  "amSignTransactionSendResult\020\226\007\032\004\230\265\030\001\0221\n&"
  "MessageType_BeamSignTransactionReceive\020\227"
  "\007\032\004\220\265\030\001\0227\n,MessageType_BeamSignTransacti"
  "onReceiveResult\020\230\007\032\004\230\265\030\001\022/\n$MessageType_"
  "BeamSignTransactionSplit\020\231\007\032\004\220\265\030\001\0225\n*Mes"
  "sageType_BeamSignTransactionSplitResult\020"
  "\232\007\032\004\230\265\030\001\022&\n\033MessageType_BeamGetNumSlots\020"
  "\233\007\032\004\220\265\030\001\022#\n\030MessageType_BeamNumSlots\020\234\007\032"
  "\004\230\265\030\001\022\"\n\027MessageType_BeamGetPKdf\020\235\007\032\004\220\265\030"
  "\001\022\037\n\024MessageType_BeamPKdf\020\236\007\032\004\230\265\030\001:4\n\007wi"
  "re_in\022!.google.protobuf.EnumValueOptions"
  "\030\322\206\003 \001(\010:5\n\010wire_out\022!.google.protobuf.E"
  "numValueOptions\030\323\206\003 \001(\010::\n\rwire_debug_in"
  "\022!.google.protobuf.EnumValueOptions\030\324\206\003 "
  "\001(\010:;\n\016wire_debug_out\022!.google.protobuf."
  "EnumValueOptions\030\325\206\003 \001(\010:6\n\twire_tiny\022!."
  "google.protobuf.EnumValueOptions\030\326\206\003 \001(\010"
  ":<\n\017wire_bootloader\022!.google.protobuf.En"
  "umValueOptions\030\327\206\003 \001(\010:8\n\013wire_no_fsm\022!."
  "google.protobuf.EnumValueOptions\030\330\206\003 \001(\010"
  "B4\n#com.satoshilabs.trezor.lib.protobufB"
  "\rTrezorMessage"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_messages_2eproto = {
  false, InitDefaults_messages_2eproto, 
  descriptor_table_protodef_messages_2eproto,
  "messages.proto", &assign_descriptors_table_messages_2eproto, 9374,
};

void AddDescriptors_messages_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
    ::AddDescriptors_google_2fprotobuf_2fdescriptor_2eproto,
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_messages_2eproto, deps, 1);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_messages_2eproto = []() { AddDescriptors_messages_2eproto(); return true; }();
namespace hw {
namespace trezor {
namespace messages {
const ::google::protobuf::EnumDescriptor* MessageType_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&assign_descriptors_table_messages_2eproto);
  return file_level_enum_descriptors_messages_2eproto[0];
}
bool MessageType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 32:
    case 34:
    case 35:
    case 36:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 45:
    case 46:
    case 47:
    case 48:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
    case 71:
    case 72:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    case 79:
    case 80:
    case 81:
    case 82:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 110:
    case 111:
    case 112:
    case 113:
    case 114:
    case 115:
    case 116:
    case 117:
    case 118:
    case 119:
    case 120:
    case 121:
    case 122:
    case 150:
    case 151:
    case 152:
    case 153:
    case 154:
    case 155:
    case 202:
    case 203:
    case 207:
    case 208:
    case 210:
    case 211:
    case 212:
    case 213:
    case 214:
    case 215:
    case 216:
    case 217:
    case 218:
    case 220:
    case 221:
    case 230:
    case 303:
    case 304:
    case 305:
    case 306:
    case 307:
    case 308:
    case 309:
    case 310:
    case 400:
    case 401:
    case 402:
    case 403:
    case 450:
    case 451:
    case 501:
    case 502:
    case 503:
    case 504:
    case 505:
    case 506:
    case 507:
    case 508:
    case 509:
    case 510:
    case 511:
    case 512:
    case 513:
    case 514:
    case 515:
    case 516:
    case 517:
    case 518:
    case 530:
    case 531:
    case 532:
    case 533:
    case 534:
    case 535:
    case 540:
    case 541:
    case 542:
    case 543:
    case 546:
    case 547:
    case 550:
    case 551:
    case 552:
    case 553:
    case 554:
    case 555:
    case 556:
    case 557:
    case 600:
    case 601:
    case 602:
    case 603:
    case 604:
    case 605:
    case 700:
    case 701:
    case 702:
    case 703:
    case 704:
    case 705:
    case 706:
    case 707:
    case 708:
    case 709:
    case 800:
    case 801:
    case 802:
    case 803:
    case 902:
    case 903:
    case 904:
    case 905:
    case 907:
    case 908:
    case 909:
    case 910:
    case 911:
    case 912:
    case 913:
    case 914:
    case 915:
    case 916:
    case 917:
    case 918:
    case 919:
    case 920:
    case 921:
    case 922:
    case 923:
    case 924:
    case 925:
    case 926:
    case 9001:
      return true;
    default:
      return false;
  }
}

::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< bool >, 8, false >
  wire_in(kWireInFieldNumber, false);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< bool >, 8, false >
  wire_out(kWireOutFieldNumber, false);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< bool >, 8, false >
  wire_debug_in(kWireDebugInFieldNumber, false);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< bool >, 8, false >
  wire_debug_out(kWireDebugOutFieldNumber, false);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< bool >, 8, false >
  wire_tiny(kWireTinyFieldNumber, false);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< bool >, 8, false >
  wire_bootloader(kWireBootloaderFieldNumber, false);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< bool >, 8, false >
  wire_no_fsm(kWireNoFsmFieldNumber, false);

// @@protoc_insertion_point(namespace_scope)
}  // namespace messages
}  // namespace trezor
}  // namespace hw
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
