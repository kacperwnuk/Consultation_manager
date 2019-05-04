//
// Created by kacper on 20.04.2019.
//

#include "MessageSender.h"

MessageSender::MessageSender() {
    messageQueue = std::make_shared < SynchronizedQueue < OutgoingMessage >> ();
}

const std::shared_ptr<SynchronizedQueue<OutgoingMessage>> &MessageSender::getMessageQueue() const {
    return messageQueue;
}

void MessageSender::run() {
    auto isRunning = true;
    while (isRunning) {
        auto message = messageQueue->get();
        write(message.fd, message.payload, message.size);
    }
}
