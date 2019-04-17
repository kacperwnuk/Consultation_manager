//
// Created by kacper on 17.04.2019.
//

#ifndef SERVER_CLIENTMESSAGEBUILDERTHREAD_H
#define SERVER_CLIENTMESSAGEBUILDERTHREAD_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include "Thread.h"
#include "containers/synchronizedcontainers/SynchronizedQueue.h"
#include "IncomingMessage.h"
#include "containers/synchronizedcontainers/MutualExclusiveHashMap.h"

class ClientMessageBuilderThread: public Thread {
private:

    int socket;
//    std::shared_ptr<SynchronizedQueue<IncomingMessage>> messageBuffer;
    MutualExclusiveHashMap<size_t> &readDemands;


public:
    ClientMessageBuilderThread(int, std::shared_ptr<SynchronizedQueue<IncomingMessage>>, MutualExclusiveHashMap<size_t> &readDemands);
    void run() override;
    char header[4];
    char *payload;
    size_t size = 0;
    bool duringBuilding = false;
    pthread_cond_t readComplete;
    pthread_mutex_t mutex;
    size_t demand = 4;
};


#endif //SERVER_CLIENTMESSAGEBUILDERTHREAD_H
