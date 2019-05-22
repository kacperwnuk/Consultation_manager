//
// Created by kacper on 20.04.2019.
//

#ifndef SERVER_MESSAGESENDER_H
#define SERVER_MESSAGESENDER_H


#include "../containers/synchronizedcontainers/SynchronizedQueue.h"
#include "../containers/OutgoingMessage.h"
#include "Thread.h"
#include <memory>

class MessageSender {
    int socket;
public:

    explicit MessageSender(int);
    void send(std::string);
};


#endif //SERVER_MESSAGESENDER_H
