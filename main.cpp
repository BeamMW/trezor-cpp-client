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
                std::cout << "BEAM OWNER KEY: " << child_cast<Message, BeamOwnerKey>(msg).key() << std::endl;
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
            trezor->call_BeamGenerateKey(0, 0, 0, 1, true, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM GENERATED PUBLIC KEY:" << std::endl;
                std::cout << "pub_x: ";
                print_bin(reinterpret_cast<const uint8_t*>(child_cast<Message, BeamECCPoint>(msg).x().c_str()), 32);
                std::cout << "pub_y: " << child_cast<Message, BeamECCPoint>(msg).y() << std::endl;
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });
            trezor->call_BeamGenerateRangeproof(0, 0, 0, 1, false, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                const uint8_t * rp_raw = reinterpret_cast<const uint8_t *>(child_cast<Message, BeamRangeproofData>(msg).data().c_str());
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM GENERATED RANGEPROOF:" << std::endl;
                std::cout << "first 64 of 688 bytes: ";
                print_bin(rp_raw, 64);

                rangeproof_confidential_packed_t rp;
                memcpy(&rp, rp_raw, sizeof(rangeproof_confidential_packed_t));
                std::cout << "mu:" << std::endl;
                print_bin(rp.mu, 32);
                std::cout << "tDot:" << std::endl;
                print_bin(rp.tDot, 32);
                std::cout << "tauX:" << std::endl;
                print_bin(rp.part3.tauX, 32);
                std::cout << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });

            std::vector<key_idv_t> inputs;
            inputs.push_back({1, 1, 1, 2});
            inputs.push_back({2, 2, 2, 5});
            std::vector<key_idv_t> outputs;
            outputs.push_back({3, 3, 3, 3});
            uint8_t test_bytes[32] = {0x87, 0xdc, 0x3d, 0x21, 0x41, 0x74, 0x82, 0x0e, 0x11, 0x54, 0xb4, 0x9b, 0xc6, 0xcd, 0xb2, 0xab, 0xd4, 0x5e, 0xe9, 0x58, 0x17, 0x05, 0x5d, 0x25, 0x5a, 0xa3, 0x58, 0x31, 0xb7, 0x0d, 0x32, 0x66};
            transaction_data_t tx_data;
            tx_data.fee = 1;
            tx_data.min_height = 1;
            tx_data.max_height = 5;
            tx_data.nonce_slot = 2;
            memcpy(tx_data.kernel_commitment.x, test_bytes, 32);
            tx_data.kernel_commitment.y = 1;
            memcpy(tx_data.kernel_nonce.x, test_bytes, 32);
            tx_data.kernel_nonce.y = 1;
            memcpy(tx_data.offset, test_bytes, 32);

            trezor->call_BeamSignTransaction(inputs, outputs, tx_data, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                const uint8_t *signature = reinterpret_cast<const uint8_t *>(child_cast<Message, BeamSignedTransaction>(msg).signature().c_str());
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM TX SIGNATURE: ";
                print_bin(reinterpret_cast<const uint8_t *>(signature), 32);
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
