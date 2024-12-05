#pragma once
#include <string>

enum class MessageType {
    String,
    Mouse,
    FloatMessage,
    Raycast,
    OBJMeshLoading,

};
class Message
{
public:
    Message(MessageType type);
    Message(MessageType type, std::string msg);

    virtual ~Message();

    MessageType type;

    std::string msg;
};
