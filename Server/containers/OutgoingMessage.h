//
// Created by Marcin on 04.04.2019.
//

#ifndef SERVER_OUTGOINGMESSAGE_H
#define SERVER_OUTGOINGMESSAGE_H


#include <string>

class OutgoingMessage {
public:
    OutgoingMessage();
    OutgoingMessage(int, char *, int);
    int fd;
    char payload[1024];
    int size;
};


#endif //SERVER_OUTGOINGMESSAGE_H
