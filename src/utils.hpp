#pragma once

#include <cstdio>
#include <iomanip>
#include <sstream>
#include <string>
#include <google/protobuf/message.h>
#include "messages.pb.h"

extern "C" inline void hex2bin(const char *hexString, const size_t sizeString, unsigned char *outBytes)
{
    uint32_t buffer = 0;
    for (size_t i = 0; i < sizeString / 2; i++)
    {
        sscanf(hexString + 2 * i, "%2X", &buffer);
        outBytes[i] = buffer;
    }
}

template <typename T>
void copy_reversed(const uint8_t *bytes, T *value)
{
    size_t size = sizeof(T);
    for (size_t i = 0, j = size - 1; i < size; i++, j--)
        *value |= static_cast<T>(bytes[j] << i * 8);
}

template <typename Container>
std::string pack_message(int type, size_t length, const Container &msg)
{
    std::ostringstream ss;
    // Write message type
    ss << std::setfill('0') << std::setw(4) << std::hex << type;
    // Write message length
    ss << std::setw(8) << std::hex << length;
    // Write message as a hex string
    for (size_t i = 0; i < length; i++)
        ss << std::setw(2) << std::hex << static_cast<int>(msg[i]);
    return ss.str();
}

std::string pack_message(const google::protobuf::Message &msg)
{
    auto name = "MessageType_" + msg.GetDescriptor()->name();
    auto msg_type = hw::trezor::messages::MessageType_descriptor()
                        ->FindValueByName(name)
                        ->number();
    auto serialized_msg = msg.SerializeAsString();

    return pack_message(msg_type, serialized_msg.size(), serialized_msg);
}
