#pragma once

#include <cstdio>
#include <iomanip>
#include <sstream>
#include <string>
#include <google/protobuf/message.h>
#include "messages.pb.h"

const uint16_t INTERNAL_ERROR = 999;

struct pair_hash
{
    template <class T>
    static inline void hash_combine(std::size_t &seed, const T &v)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        std::size_t seed = 0;
        hash_combine(seed, p.first);
        hash_combine(seed, p.second);
        return seed;
    }
};

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
    {
        auto byte = static_cast<uint32_t>(static_cast<uint8_t>(msg[i]));
        ss << std::setw(2) << std::hex << byte;
    }
    return ss.str();
}

inline std::string pack_message(const google::protobuf::Message &msg)
{
    auto name = "MessageType_" + msg.GetDescriptor()->name();
    auto msg_type = hw::trezor::messages::MessageType_descriptor()
                        ->FindValueByName(name)
                        ->number();
    auto serialized_msg = msg.SerializeAsString();

    return pack_message(msg_type, serialized_msg.size(), serialized_msg);
}

inline std::string get_message_type_name(int type)
{
    if (type == INTERNAL_ERROR)
        return "CLIENT INTERNAL ERROR";

    auto name = hw::trezor::messages::MessageType_descriptor()
                    ->FindValueByNumber(type)
                    ->name();

    auto prefix = std::string("MessageType_");
    auto i = name.find(prefix);
    if (i != std::string::npos)
        name.erase(i, prefix.length());
    return name;
}

template <typename Parrent, typename Child>
const Child &child_cast(const Parrent &message)
{
    return *dynamic_cast<const Child *>(&message);
}
