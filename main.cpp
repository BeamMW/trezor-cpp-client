#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <iterator>
#include "client.hpp"
#include "queue/call_queue.h"

#include <google/protobuf/message.h>
using namespace google::protobuf;

#include "messages-management.pb.h"
#include "messages-common.pb.h"
#include "messages-beam.pb.h"
#include "messages.pb.h"
using namespace hw::trezor::messages::management;
using namespace hw::trezor::messages::beam;
using namespace hw::trezor::messages::common;
using namespace hw::trezor::messages;

template <typename T>
void print_bin(T msg)
{
    for (size_t i = 0; i < msg.size(); i++)
        printf("%02x", msg[i]);
    printf("\n");
}

void print_call_response(const Call &value)
{
    std::cout << "call.error = " << value.error << std::endl;
    std::cout << "call.type = " << value.type
              << " (" << get_message_type_name(value.type) << ")" << std::endl;
    std::cout << "call.length = " << value.length << std::endl;
    std::cout << "call.msg = ";
    print_bin(value.msg);

    if (MessageType::MessageType_Failure == value.type)
    {
        auto msg(value.to_message<Failure>());
        std::cout << "FAIL REASON: " << msg.message() << std::endl;
    }
    else if (MessageType::MessageType_BeamOwnerKey == value.type)
    {
        auto msg(value.to_message<BeamOwnerKey>());
        std::cout << "OWNER KEY: " << msg.key() << std::endl;
    }
}

int main()
{
    Client client;
    CallQueue queue;
    queue.setPopCallback([&](std::string session, const Call &call) {
        print_call_response(call);
        if (MessageType::MessageType_ButtonRequest == call.type)
        {
            queue.push(session, pack_message(ButtonAck()), [&](const std::string &in_session, const std::string &in_message) {
                return client.call(in_session, in_message);
            });
        }
    });

    BeamGetOwnerKey bmsg;
    bmsg.set_show_display(true);
    auto packed = pack_message(bmsg);

    auto enumerates = client.enumerate();
    std::cout << "enumerate.session = " << enumerates[0].session << std::endl;
    auto session = client.acquire(enumerates[0].path, enumerates[0].session);
    std::cout << "acquire.session = " << session.session << std::endl;

    queue.push(session.session, packed, [&](const std::string &session, const std::string &message) {
        return client.call(session, message);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    curl_global_cleanup();
    return 0;
}
