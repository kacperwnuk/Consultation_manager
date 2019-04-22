//
// Created by kacper on 20.04.2019.
//

#ifndef SERVER_MESSAGESENDER_H
#define SERVER_MESSAGESENDER_H


#include "containers/synchronizedcontainers/SynchronizedQueue.h"
#include "containers/OutgoingMessage.h"
#include "Thread.h"
#include <memory>

class MessageSender : public Thread{
    std::shared_ptr<SynchronizedQueue<OutgoingMessage>> messageQueue;
public:
    const std::shared_ptr<SynchronizedQueue<OutgoingMessage>> &getMessageQueue() const;

public:
    MessageSender();
    void run() override;
};


#endif //SERVER_MESSAGESENDER_H
