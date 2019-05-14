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

class ClientInOutAction : public Thread {
private:
    SynchronizedQueue<Request *> &inQueue;
    SynchronizedQueue<Serializable *> &outQueue;
    Serializer serializer;
    Deserializer deserializer;
    ClientMessageBuilder clientMessageBuilder;
    MessageSender messageSender;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    bool isRunning = true;
    bool readyToRead = false;
    bool readyToWrite = false;
    // from Client
    bool &readyToSend;
    bool &readyToReceive;


    void handleInMessage();

    void handleOutMessage();

public:

    explicit ClientInOutAction(int, SynchronizedQueue<Request *> &,
                               SynchronizedQueue<Serializable *> &, bool &, bool &);

    void run() override;

    void send();

    void receive();

};


#endif //SERVER_CLIENTINOUTACTION_H
