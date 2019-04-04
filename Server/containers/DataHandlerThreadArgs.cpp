//
// Created by Marcin on 04.04.2019.
//

#include "DataHandlerThreadArgs.h"

DataHandlerThreadArgs::DataHandlerThreadArgs(SynchronizedQueue<OutgoingMessage> &messages, SynchronizedVector<int> &sockets, bool &stopCond): SocketOperatingThreadArgs(sockets), OutThreadArgs(messages, stopCond) {

}
