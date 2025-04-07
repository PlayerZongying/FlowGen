#pragma once
#include <queue>
#include "Message.h"
#include <mutex>
#include <condition_variable>
#include <thread>

class MessageQueue
{
public:

    virtual void QueueMessage(Message* msg) = 0;

private:


    
};
