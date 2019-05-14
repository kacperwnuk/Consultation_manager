//
// Created by Marcin on 14.05.2019.
//

#include "ClientInOutAction.h"

void ClientInOutAction::run() {
    while (isRunning) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&condition, &mutex);
        if (readyToRead) {
            readyToRead = false;
            handleInMessage();
        }
        if (readyToWrite) {
            readyToWrite = false;
            handleOutMessage();
        }
        pthread_mutex_unlock(&mutex);
    }
}


void ClientInOutAction::send() {
    readyToWrite = true;
    std::cout << pthread_cond_signal(&condition) << std::endl;
}

void ClientInOutAction::receive() {
    readyToRead = true;
    std::cout << pthread_cond_signal(&condition) << std::endl;
}


ClientInOutAction::ClientInOutAction(int socket, SynchronizedQueue<Request *> &inQueue,
                                     SynchronizedQueue<Serializable *> &outQueue, bool &readyToSend, bool &readyToReceive)
        : clientMessageBuilder(socket),
          inQueue(inQueue), outQueue(outQueue), messageSender(socket), readyToSend(readyToSend), readyToReceive(readyToReceive) {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&condition, nullptr);
}

void ClientInOutAction::handleInMessage() {
    auto message = clientMessageBuilder.getMessage();
    auto *request = deserializer.getDeserializedObject(message);
    inQueue.put(request);
}

void ClientInOutAction::handleOutMessage() {
    auto *response = outQueue.get();
    auto message = serializer.serialize(response);
    messageSender.send(message);
    if (outQueue.getSize() == 0) {
        readyToSend = false;
    }
}
