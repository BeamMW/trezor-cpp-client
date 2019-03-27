#include <iostream>
#include <string>
#include <sstream>
#include "client.hpp"
#include <iomanip>
#include <iterator>

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

int main(void)
{
    Client client;

    BeamGetOwnerKey bmsg;
    bmsg.set_show_display(true);
    auto packed = pack_message(bmsg);

    auto enumerates = client.enumerate();
    std::cout << "enumerate.session = " << enumerates[0].session << std::endl;
    auto session = client.acquire(enumerates[0].path, enumerates[0].session);
    std::cout << "acquire.session = " << session.session << std::endl;

    auto call = client.call(session.session, packed);
    print_call_response(call);
    while (MessageType::MessageType_ButtonRequest == call.type)
    {
        call = client.call(session.session, pack_message(ButtonAck()));
        print_call_response(call);
    }

    curl_global_cleanup();
    return 0;
}
