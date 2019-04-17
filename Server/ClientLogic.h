//
// Created by Marcin on 17.04.2019.
//

#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H


#include <string>
#include "Thread.h"
#include "ClientMessageBuilder.h"

class ClientLogic: public Thread {
    int socket;
    MutualExclusiveHashMap<size_t> &readDemands;
public:
    ClientLogic(int, MutualExclusiveHashMap<size_t> &);
    ClientMessageBuilder *clientMessageBuilder;
    void run() override;
};


#endif //SERVER_PARSER_H
