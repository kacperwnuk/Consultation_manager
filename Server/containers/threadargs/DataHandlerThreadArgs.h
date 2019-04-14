//
// Created by Marcin on 04.04.2019.
//

#ifndef SERVER_DATAHANDLERTHREADARGS_H
#define SERVER_DATAHANDLERTHREADARGS_H


#include "OutThreadArgs.h"
#include "SocketOperatingThreadArgs.h"

class DataHandlerThreadArgs: public OutThreadArgs, public SocketOperatingThreadArgs {
public:
    DataHandlerThreadArgs(SynchronizedQueue<OutgoingMessage> &, SynchronizedVector<int> &, bool &);
};


#endif //SERVER_DATAHANDLERTHREADARGS_H
