#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <google/protobuf/message.h>
using namespace google::protobuf;

#include "messages/messages.pb.h"
#include "messages/messages-management.pb.h"
#include "messages/messages-common.pb.h"
#include "messages/messages-beam.pb.h"
using namespace hw::trezor::messages;
using namespace hw::trezor::messages::management;
using namespace hw::trezor::messages::beam;

std::string pack_message(const Message& msg) {
    std::stringstream ss;

    auto name = "MessageType_" + msg.GetDescriptor()->name();
    int msg_type = MessageType_descriptor()->FindValueByName(name)->number();

    // Write message type
    ss << std::setfill('0') << std::setw(4) << std::hex << msg_type;

    std::string serialized_msg;
    msg.SerializeToString(&serialized_msg);

    // Write message length
    ss << std::setw(8) << std::hex << serialized_msg.size();
    for (auto c: serialized_msg)
        ss << std::setw(2) << std::hex << static_cast<int>(c);
    return ss.str();
}
