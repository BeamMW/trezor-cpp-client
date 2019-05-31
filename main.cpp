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
        is_alive_flags.push_back(std::unique_ptr<std::atomic_flag>(new std::atomic_flag(1)));
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
            clear_flag(queue_size, is_alive_idx);
        });

        trezor->callback_Success([&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
            std::cout << "SESSION: " << session << std::endl;
            std::cout << "SUCCESS: " << child_cast<Message, Success>(msg).message() << std::endl;
            clear_flag(queue_size, is_alive_idx);
        });

        try
        {
            using namespace hw::trezor::messages::beam;
            
            trezor->init(enumerate);
            trezor->call_Ping("hello beam", true, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "PONG: " << child_cast<Message, Success>(msg).message() << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });
            trezor->call_BeamGetOwnerKey(true, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM OWNER KEY: " << child_cast<Message, BeamOwnerKey>(msg).key() << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });
            trezor->call_BeamGenerateNonce(1, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM NONCE IN SLOT 1: " << std::endl;
                std::cout << "pub_x: ";
                print_bin(reinterpret_cast<const uint8_t *>(child_cast<Message, BeamECCPoint>(msg).x().c_str()), 32);
                std::cout << "pub_y: " << child_cast<Message, BeamECCPoint>(msg).y() << std::endl;
                clear_flag(queue_size, is_alive_idx);
            });
            trezor->call_BeamGetNoncePublic(1, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM PUBLIC KEY OF NONCE IN SLOT 1:" << std::endl;
                std::cout << "pub_x: ";
                print_bin(reinterpret_cast<const uint8_t *>(child_cast<Message, BeamPublicKey>(msg).pub_x().c_str()), 32);
                std::cout << "pub_y: ";
                print_bin(reinterpret_cast<const uint8_t *>(child_cast<Message, BeamPublicKey>(msg).pub_y().c_str()), 1);
                clear_flag(queue_size, is_alive_idx);
            });
            trezor->call_BeamGenerateKey(0, 0, 0, 1, true, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM GENERATED PUBLIC KEY:" << std::endl;
                std::cout << "pub_x: ";
                print_bin(reinterpret_cast<const uint8_t*>(child_cast<Message, BeamPublicKey>(msg).pub_x().c_str()), 32);
                std::cout << "pub_y: ";
                print_bin(reinterpret_cast<const uint8_t*>(child_cast<Message, BeamPublicKey>(msg).pub_y().c_str()), 1);
                clear_flag(queue_size, is_alive_idx);
            });
            trezor->call_BeamGenerateRangeproof(0, 0, 0, 1, false, [&, is_alive_idx](const Message &msg, std::string session, size_t queue_size) {
                const uint8_t * rp_raw = reinterpret_cast<const uint8_t *>(child_cast<Message, BeamRangeproofData>(msg).data().c_str());
                std::cout << "SESSION: " << session << std::endl;
                std::cout << "BEAM GENERATED RANGEPROOF:" << std::endl;
                std::cout << "first 64 of 688 bytes: ";
                print_bin(rp_raw, 64);

                rangeproof_confidential_t rp;
                memcpy(&rp, rp_raw, sizeof(rangeproof_confidential_t));
                std::cout << "mu:" << std::endl;
                print_bin(reinterpret_cast<const uint8_t *>(&rp.mu), 32);
                std::cout << "tDot:" << std::endl;
                print_bin(reinterpret_cast<const uint8_t *>(&rp.tDot), 32);
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
