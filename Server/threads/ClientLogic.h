//
// Created by Marcin on 17.04.2019.
//

#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H


#include <string>
#include "Thread.h"
#include "../containers/synchronizedcontainers/SynchronizedQueue.h"
#include "../dto/Request.h"
#include "../serialization/Serializable.h"

class ClientLogic : public Thread {
    SynchronizedQueue<Request*>& inQueue;
    SynchronizedQueue<Serializable*>& outQueue;
    bool &readyToSend;
    int pipe;
public:
    ClientLogic(SynchronizedQueue<Request*>&, SynchronizedQueue<Serializable*>&, bool &, int);

    void run() override;
};


#endif //SERVER_PARSER_H
