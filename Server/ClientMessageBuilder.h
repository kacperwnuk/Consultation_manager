//
// Created by kacper on 17.04.2019.
//

#ifndef SERVER_CLIENTMESSAGEBUILDERTHREAD_H
#define SERVER_CLIENTMESSAGEBUILDERTHREAD_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include "threads/Thread.h"
#include "containers/synchronizedcontainers/SynchronizedQueue.h"
#include "Message.h"
#include "containers/synchronizedcontainers/MutualExclusiveHashMap.h"

class ClientMessageBuilder {
private:

    int socket;
    MutualExclusiveHashMap<size_t> &readDemands;

    size_t getHeader();

    std::string getPayload(size_t);

public:
    ClientMessageBuilder(int, MutualExclusiveHashMap<size_t> &readDemands);

    std::string getMessage();

    char header[4];
    char *payload;
    size_t size = 0;
    pthread_cond_t readComplete;
    pthread_mutex_t mutex;
    size_t demand = 4;
    bool gettingHeader = true;
};


#endif //SERVER_CLIENTMESSAGEBUILDERTHREAD_H
