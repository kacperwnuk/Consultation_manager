//
// Created by Marcin on 07.04.2019.
//

#include "ListenerThreadArgs.h"

ListenerThreadArgs::ListenerThreadArgs(SynchronizedVector<int> &sockets, bool &stopCond, in_port_t port):
    StoppableThreadArgs(stopCond), SocketOperatingThreadArgs(sockets), port(port) {

}
