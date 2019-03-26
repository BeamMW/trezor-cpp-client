#include <iostream>
#include <string>
#include <sstream>
#include "client.hpp"

int main(void)
{
    Client client;

    auto enumerates = client.enumerate();
    auto session = client.acquire(enumerates[0].path, enumerates[0].session);
    // auto call = client.call(session.session, "00010000000B0a0948692c2070696e6721");
    auto call = client.call(session.session, "02c3000000020801");

    std::cout << "enumerate.session = " << enumerates[0].session << std::endl;
    std::cout << "acquire.session = " << session.session << std::endl;
    std::cout << "call.error = " << call.error << std::endl;
    std::cout << "call.type = " << call.type << std::endl;
    std::cout << "call.length = " << call.length << std::endl;
    std::cout << "call.msg = ";
    for (size_t i = 0; i < call.msg.size(); i++)
        printf("%02x", call.msg[i]);
    std::cout << std::endl;
    std::cout << "discard_pin.expected = " << "0003 00000012 120e4669726d77617265206572726f720863" << std::endl;
    curl_global_cleanup();
    return 0;
}
