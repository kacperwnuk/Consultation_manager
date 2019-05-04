//
// Created by kacper on 17.04.2019.
//

#include "ClientMessageBuilder.h"

std::string ClientMessageBuilder::getMessage() {
    return getPayload(getHeader());
}

ClientMessageBuilder::ClientMessageBuilder(int socket,
                                           MutualExclusiveHashMap<size_t> &readDemands) : readDemands(readDemands) {
    this->socket = socket;
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&readComplete, nullptr);
    size = 0;
}

size_t ClientMessageBuilder::getHeader() {
    gettingHeader = true;
    demand = 4;
    readDemands.put(socket, demand);
    pthread_mutex_lock(&mutex);
    if (size < demand) {
        pthread_cond_wait(&readComplete, &mutex);
    }
    demand = static_cast<size_t>(atoi(header));
    payload = new char[demand];
    readDemands.put(socket, demand);
    size = 0;
    pthread_mutex_unlock(&mutex);

    return demand;
}

std::string ClientMessageBuilder::getPayload(size_t) {
    gettingHeader = false;
    pthread_mutex_lock(&mutex);
    if (size < demand) {
        pthread_cond_wait(&readComplete, &mutex);
    }
    std::string messagePayload = payload;
    delete[] payload;
    size = 0;
    pthread_mutex_unlock(&mutex);
    return messagePayload;
}
