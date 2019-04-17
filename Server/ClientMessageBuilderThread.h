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

class ClientMessageBuilderThread: public Thread {
private:
    int socket;
    std::shared_ptr<SynchronizedQueue<IncomingMessage>> messageBuffer;
    bool duringBuilding = false;
public:
    ClientMessageBuilderThread(int, std::shared_ptr<SynchronizedQueue<IncomingMessage>>);
    void run() override;

};


#endif //SERVER_CLIENTMESSAGEBUILDERTHREAD_H
