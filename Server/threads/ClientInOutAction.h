//
// Created by Marcin on 14.05.2019.
//

#ifndef SERVER_CLIENTINOUTACTION_H
#define SERVER_CLIENTINOUTACTION_H


#include <pthread.h>
#include "Thread.h"
#include "../serialization/Serializer.h"
#include "../serialization/Deserializer.h"
#include "../ClientMessageBuilder.h"
#include "../containers/synchronizedcontainers/SynchronizedQueue.h"
#include "MessageSender.h"
#include "Encryption.h"

class ClientInOutAction {
private:
    int fd;
    bool &connected;
    SynchronizedQueue<std::unique_ptr<Request>> &inQueue;
    SynchronizedQueue<std::unique_ptr<Serializable>> &outQueue;
    Serializer serializer;
    Deserializer deserializer;

    char header[4];
    char* payload;
    bool readingHeader = true;
    bool payloadAllocated = false;
    size_t bytesRead = 0;
    size_t bytesToRead = 4;

    bool writing;
    std::string message;
    size_t bytesToWrite;
    size_t bytesWritten;

    bool &wantsToWrite;

    Encryption encryption;


public:

    explicit ClientInOutAction(int, SynchronizedQueue<std::unique_ptr<Request>> &,
                               SynchronizedQueue<std::unique_ptr<Serializable>> &, bool&, bool &);

    void send();

    void receive();

    void disconnect(){connected = false;}

};


#endif //SERVER_CLIENTINOUTACTION_H
