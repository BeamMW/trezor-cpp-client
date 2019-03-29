#include <iostream>
#include <string>
#include "client.hpp"
#include "queue/working_queue.h"
#include "device_manager.hpp"

#include "debug.hpp"

int main()
{
    Client client;
    DeviceManager trezor;

    auto enumerates = client.enumerate();
    if (enumerates[0].session != "null")
    {
        client.release(enumerates[0].session);
        enumerates[0].session = "null";
    }

    trezor.set_callback(MessageType_Failure, [](const Message &msg) {
        std::cout << "FAIL REASON: " << child_cast<Message, Failure>(msg).message() << std::endl;
    });

    trezor.init(enumerates[0]);
    trezor.call_BeamGetOwnerKey(true, [](const Message &msg) {
        std::cout << "BEAM OWNER KEY: " << child_cast<Message, BeamOwnerKey>(msg).key() << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    curl_global_cleanup();
    return 0;
}
