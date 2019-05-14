//
// Created by kacper on 17.04.2019.
//

#ifndef SERVER_CLIENTMESSAGEBUILDERTHREAD_H
#define SERVER_CLIENTMESSAGEBUILDERTHREAD_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include <unistd.h>
#include "threads/Thread.h"
#include "Message.h"

class ClientMessageBuilder {
private:

    int socket;

    size_t getHeader();

    std::string getPayload(size_t);

    std::string readBytes(size_t bytesToRead);



public:
    ClientMessageBuilder(int);

    std::string getMessage();

    char *payload;

    class ReadException : public std::exception {
    public:
        const char *what() const noexcept override;
    };
};


#endif //SERVER_CLIENTMESSAGEBUILDERTHREAD_H
