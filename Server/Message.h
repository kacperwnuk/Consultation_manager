//
// Created by kacper on 17.04.2019.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H


class Message {

public:
    int size;
    char* payload;
    Message(int, char*);
    Message();
    ~Message();
};


#endif //SERVER_MESSAGE_H
