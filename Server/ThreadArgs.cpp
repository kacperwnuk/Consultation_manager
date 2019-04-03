//
// Created by Marcin on 02.04.2019.
//

#include "ThreadArgs.h"

ThreadArgs::ThreadArgs(SynchronizedVector<int> &sockets, bool &stopCond): stopCond(stopCond), sockets(sockets) {
}

SynchronizedVector<int> &ThreadArgs::getSockets() {
    return sockets;
}

bool &ThreadArgs::getStopCond() {
    return stopCond;
}
