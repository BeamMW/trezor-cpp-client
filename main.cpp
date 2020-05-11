#include <iostream>
#include <string>
#include "client.hpp"
#include "queue/working_queue.h"
#include "device_manager.hpp"

#include "debug.hpp"
#include "hw_definitions.hpp"

int main()
{
    Client client;
    std::vector<std::unique_ptr<DeviceManager>> trezors;
    std::vector<std::unique_ptr<std::atomic_flag>> is_alive_flags;

    auto enumerates = client.enumerate();

    if (enumerates.size() == 0)
    {
        std::cout << "there is no device connected" << std::endl;
        return 1;
    }

    auto clear_flag = [&](size_t queue_size, size_t idx) {
        if (queue_size == 0)
            is_alive_flags.at(idx)->clear();
    };

    for (auto enumerate : enumerates)
    {
        trezors.push_back(std::unique_ptr<DeviceManager>(new DeviceManager()));
        {
            auto af = std::make_unique<std::atomic_flag>();
            af->test_and_set();
            is_alive_flags.emplace_back(move(af));
        }
        auto is_alive_idx = is_alive_flags.size() - 1;
        auto& trezor = trezors.back();

        if (enumerate.session != "null")
        {
            client.release(enumerate.session);
            enumerate.session = "null";
        }

        trezor->callback_Failure([&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
            std::cout << "SESSION: " << session << std::endl;
            std::cout << "FAIL REASON: " << child_cast<Message, Failure>(msg).message() << std::endl;
            std::cout << std::endl;
            clear_flag(queue_size, is_alive_idx);
        });

        trezor->callback_Success([&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
            std::cout << "SESSION: " << session << std::endl;
            std::cout << "SUCCESS: " << child_cast<Message, Success>(msg).message() << std::endl;
            std::cout << std::endl;
            clear_flag(queue_size, is_alive_idx);
        });

        try
        {
            using namespace hw::trezor::messages::beam;
            
            trezor->init(enumerate);
            trezor->call_Ping("hello beam", true, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "PONG: " << child_cast<Message, Success>(msg).message() << std::endl;
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });
            trezor->call_BeamGetOwnerKey(true, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM OWNER KEY: ";
                print_bin(reinterpret_cast<const uint8_t *>(child_cast<Message, BeamOwnerKey>(msg).key().c_str()), 32);
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });
            trezor->call_BeamGenerateNonce(1, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM NONCE IN SLOT 1: " << std::endl;
                std::cout << "pub_x: ";
                print_bin(reinterpret_cast<const uint8_t *>(child_cast<Message, BeamECCPoint>(msg).x().c_str()), 32);
                std::cout << "pub_y: " << child_cast<Message, BeamECCPoint>(msg).y() << std::endl;
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });
            trezor->call_BeamGetNoncePublic(1, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM PUBLIC KEY OF NONCE IN SLOT 1:" << std::endl;
                std::cout << "pub_x: ";
                print_bin(reinterpret_cast<const uint8_t *>(child_cast<Message, BeamECCPoint>(msg).x().c_str()), 32);
                std::cout << "pub_y: " << child_cast<Message, BeamECCPoint>(msg).y() << std::endl;
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });

            uint8_t test_bytes[32] = {0x87, 0xdc, 0x3d, 0x21, 0x41, 0x74, 0x82, 0x0e, 0x11, 0x54, 0xb4, 0x9b, 0xc6, 0xcd, 0xb2, 0xab, 0xd4, 0x5e, 0xe9, 0x58, 0x17, 0x05, 0x5d, 0x25, 0x5a, 0xa3, 0x58, 0x31, 0xb7, 0x0d, 0x32, 0x66};
            std::vector<BeamCrypto_CoinID> inputs;
            inputs.push_back({1, 1, 1, 2, 0});
            inputs.push_back({2, 2, 2, 5, 0});
            std::vector<BeamCrypto_CoinID> outputs;
            outputs.push_back({3, 3, 3, 3, 0});

            BeamCrypto_TxCommon txCommon;
            txCommon.m_pIns = &inputs;
            txCommon.m_pOuts = &outputs;
            memcpy(txCommon.m_kOffset.m_pVal, test_bytes, 32);
            txCommon.m_Krn.m_Fee = 20;
            txCommon.m_Krn.m_hMin = 3;
            txCommon.m_Krn.m_hMax = 43;
            memcpy(txCommon.m_Krn.m_Commitment.m_X.m_pVal, test_bytes, 32);
            txCommon.m_Krn.m_Commitment.m_Y = 1;
            memcpy(txCommon.m_Krn.m_Signature.m_k.m_pVal, test_bytes, 32);
            txCommon.m_Krn.m_Signature.m_NoncePub.m_Y = 1;
            memcpy(txCommon.m_Krn.m_Signature.m_NoncePub.m_X.m_pVal, test_bytes, 32);

            BeamCrypto_TxMutualInfo txMutualInfo;
            memcpy(txMutualInfo.m_Peer.m_pVal, test_bytes, 32);
            txMutualInfo.m_MyIDKey = 25;
            memcpy(txMutualInfo.m_PaymentProofSignature.m_NoncePub.m_X.m_pVal, test_bytes, 32);
            txMutualInfo.m_PaymentProofSignature.m_NoncePub.m_Y = 1;
            memcpy(txMutualInfo.m_PaymentProofSignature.m_k.m_pVal, test_bytes, 32);

            BeamCrypto_TxSenderParams txSenderParams;
            txSenderParams.m_iSlot = 2;
            memset(txSenderParams.m_UserAgreement.m_pVal, 0, 32);

            trezor->call_BeamSignTransactionSend(txCommon, txMutualInfo, txSenderParams, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                const uint8_t *offset_sk = reinterpret_cast<const uint8_t *>(child_cast<Message, BeamSignTransactionSend>(msg).tx_common().offset_sk().c_str());
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BeamSignTransactionSend" << std::endl;
                std::cout << "BEAM TX offset_sk: ";
                print_bin(reinterpret_cast<const uint8_t *>(offset_sk), 32);
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });

            trezor->call_BeamSignTransactionReceive(txCommon, txMutualInfo, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                const uint8_t *offset_sk = reinterpret_cast<const uint8_t *>(child_cast<Message, BeamSignTransactionReceive>(msg).tx_common().offset_sk().c_str());
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BeamSignTransactionReceive" << std::endl;
                std::cout << "BEAM TX offset_sk: ";
                print_bin(reinterpret_cast<const uint8_t *>(offset_sk), 32);
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });

            trezor->call_BeamSignTransactionSplit(txCommon, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                const uint8_t *offset_sk = reinterpret_cast<const uint8_t *>(child_cast<Message, BeamSignTransactionSplit>(msg).tx_common().offset_sk().c_str());
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BeamSignTransactionSplit" << std::endl;
                std::cout << "BEAM TX offset_sk: ";
                print_bin(reinterpret_cast<const uint8_t *>(offset_sk), 32);
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });

            BeamCrypto_CoinID cid = {1, 1, 1, 2, 0};
            BeamCrypto_CompactPoint pt0;
            memcpy(pt0.m_X.m_pVal, test_bytes, 32);
            pt0.m_Y = 1;
            BeamCrypto_CompactPoint pt1;
            memcpy(pt1.m_X.m_pVal, test_bytes, 32);
            pt1.m_Y = 1;

            trezor->call_BeamGenerateRangeproof(&cid, &pt0, &pt1, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                bool is_successful = child_cast<Message, BeamRangeproofData>(msg).is_successful();
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BeamGenerateRangeproof" << std::endl;
                std::cout << "is_successful: " << is_successful << std::endl;
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });

            // trezor->call_BeamCreateOutput(0, &cid, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
            //     bool is_successful = child_cast<Message, BeamRangeproofData>(msg).is_successful();
            //     std::cout << "SESSION: " << session << std::endl;
            //     std::cout << "BeamCreateOutput" << std::endl;
            //     std::cout << "is_successful: " << is_successful << std::endl;
            //     std::cout << std::endl;
            //     clear_flag(queue_size, is_alive_idx);
            // });

            trezor->call_BeamGetPKdf(false, 1, true, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                const uint8_t *key = reinterpret_cast<const uint8_t *>(child_cast<Message, BeamPKdf>(msg).key().c_str());
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BeamGetPKdf" << std::endl;
                std::cout << "key: ";
                print_bin(reinterpret_cast<const uint8_t *>(key), 32);
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });

            trezor->call_BeamGetNumSlots(true, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                uint32_t num_slots = child_cast<Message, BeamNumSlots>(msg).num_slots();
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BeamGetNumSlots" << std::endl;
                std::cout << "num_slots: " << num_slots << std::endl;
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });
        }
        catch (std::runtime_error e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    for (auto& is_alive : is_alive_flags)
        while (is_alive->test_and_set())
            ; // waiting
    curl_global_cleanup();
    return 0;
}
