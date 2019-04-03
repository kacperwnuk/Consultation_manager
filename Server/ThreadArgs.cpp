//
// Created by Marcin on 02.04.2019.
//

#include "ThreadArgs.h"

ThreadArgs::ThreadArgs(SynchronizedVector<int> *sockets, bool *stopCond) {
    this->sockets = sockets;
    this->stopCond = stopCond;
}

SynchronizedVector<int> *ThreadArgs::getSockets() {
    return sockets;
}

bool *ThreadArgs::getStopCond() {
    return stopCond;
}
