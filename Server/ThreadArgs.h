//
// Created by Marcin on 02.04.2019.
//

#ifndef SERVER_THREADARGS_H
#define SERVER_THREADARGS_H


#include "SynchronizedVector.h"

class ThreadArgs {
private:
    SynchronizedVector<int> &sockets;
    bool &stopCond;
public:
    ThreadArgs(SynchronizedVector<int> &, bool &);
    SynchronizedVector<int> &getSockets();
    bool &getStopCond();
};

#endif //SERVER_THREADARGS_H
