//
// Created by Marcin on 02.04.2019.
//

#include "ThreadArgs.h"

ThreadArgs::ThreadArgs(SynchronizedVector<int> &sockets, bool &stopCond): StoppableThreadArgs(stopCond), SocketOperatingThreadArgs(sockets) {
}
