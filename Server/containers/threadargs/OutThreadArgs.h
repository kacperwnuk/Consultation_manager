//
// Created by Marcin on 04.04.2019.
//

#ifndef SERVER_OUTTHREADARGS_H
#define SERVER_OUTTHREADARGS_H


#include "../synchronizedcontainers/SynchronizedQueue.h"
#include "../OutgoingMessage.h"
#include "StoppableThreadArgs.h"

class OutThreadArgs: public StoppableThreadArgs {
public:
    OutThreadArgs(SynchronizedQueue<OutgoingMessage> &, bool &);

    SynchronizedQueue<OutgoingMessage> &messages;
};


#endif //SERVER_OUTTHREADARGS_H
