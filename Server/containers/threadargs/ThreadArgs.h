//
// Created by Marcin on 02.04.2019.
//

#ifndef SERVER_THREADARGS_H
#define SERVER_THREADARGS_H


#include "../synchronizedcontainers/SynchronizedVector.h"
#include "StoppableThreadArgs.h"
#include "SocketOperatingThreadArgs.h"

class ThreadArgs: public StoppableThreadArgs, public SocketOperatingThreadArgs {
public:
    ThreadArgs(SynchronizedVector<int> &, bool &);

};

#endif //SERVER_THREADARGS_H
