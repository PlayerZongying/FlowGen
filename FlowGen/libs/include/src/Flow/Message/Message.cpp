#include "Message.h"

Message::Message(MessageType type):type(type)
{
}

Message::Message(MessageType type, std::string msg):type(type), msg(msg)
{
}

Message::~Message()
{
}
