//
// Created by Marcin on 07.04.2019.
//

#ifndef SERVER_LISTENERTHREADARGS_H
#define SERVER_LISTENERTHREADARGS_H


#include <netinet/in.h>
#include "../synchronizedcontainers/SynchronizedVector.h"
#include "StoppableThreadArgs.h"
#include "SocketOperatingThreadArgs.h"

class ListenerThreadArgs: public StoppableThreadArgs, public SocketOperatingThreadArgs {
public:
    in_port_t port;
    ListenerThreadArgs(SynchronizedVector<int> &, bool &, in_port_t);

};


#endif //SERVER_LISTENERTHREADARGS_H
