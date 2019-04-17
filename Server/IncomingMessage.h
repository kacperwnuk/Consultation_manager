//
// Created by kacper on 17.04.2019.
//

#ifndef SERVER_INCOMINGMESSAGE_H
#define SERVER_INCOMINGMESSAGE_H


class IncomingMessage {

public:
    int size;
    char* payload;
    IncomingMessage(int, char*);
    IncomingMessage();
    ~IncomingMessage();
};


#endif //SERVER_INCOMINGMESSAGE_H
