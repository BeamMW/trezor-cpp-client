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
using namespace hw::trezor::messages;

template <typename T>
void print_bin(T msg)
{
    for (size_t i = 0; i < msg.size(); i++)
        printf("%02x", msg[i]);
    printf("\n");
}

int main(void)
{
    Client client;

    BeamGetOwnerKey bmsg;
    bmsg.set_show_display(true);
    auto packed = pack_message(bmsg);

    auto enumerates = client.enumerate();
    auto session = client.acquire(enumerates[0].path, enumerates[0].session);
    // auto call = client.call(session.session, "00010000000B0a0948692c2070696e6721");
    auto call = client.call(session.session, packed);

    std::cout << "BeamGetOwnerKey = " << packed << std::endl;
    std::cout << "enumerate.session = " << enumerates[0].session << std::endl;
    std::cout << "acquire.session = " << session.session << std::endl;
    std::cout << "call.error = " << call.error << std::endl;
    std::cout << "call.type = " << call.type << std::endl;
    std::cout << "call.length = " << call.length << std::endl;
    std::cout << "call.msg = ";
    print_bin(call.msg);
    std::cout << std::endl;
    std::cout << "discard_pin.expected = " << "0003 00000012 120e4669726d77617265206572726f720863" << std::endl;
    curl_global_cleanup();
    return 0;
}
