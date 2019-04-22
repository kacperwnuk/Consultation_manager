//
// Created by Marcin on 04.04.2019.
//

#ifndef SERVER_OUTGOINGMESSAGE_H
#define SERVER_OUTGOINGMESSAGE_H


#include <string>

class OutgoingMessage {
public:
    OutgoingMessage();
    OutgoingMessage(int, const char *, int);
    int fd;
    char* payload;
    int size;
};


#endif //SERVER_OUTGOINGMESSAGE_H
