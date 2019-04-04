//
// Created by Marcin on 04.04.2019.
//

#ifndef SERVER_SOCKETOPERATINGTHREADARGS_H
#define SERVER_SOCKETOPERATINGTHREADARGS_H


#include "SynchronizedVector.h"

class SocketOperatingThreadArgs {
public:
    SocketOperatingThreadArgs(SynchronizedVector<int> &);
    SynchronizedVector<int> &sockets;
};


#endif //SERVER_SOCKETOPERATINGTHREADARGS_H
