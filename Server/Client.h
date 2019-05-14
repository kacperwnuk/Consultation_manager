//
// Created by Marcin on 14.05.2019.
//

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H


#include "threads/ClientLogic.h"
#include "threads/MessageSender.h"
#include "threads/ClientInOutAction.h"

/**
 * Client wysyła wiadomości
 * Client odbiera wiadomości
 * Client mówi, czy chce coś odebrać
 * Cleint mówi, czy chce coś wysłać
 * Client trzyma swój file deskryptor
 *
 *
 *
 */
class Client {
private:
    int fd;
    bool readyToReceive = true;
    bool readyToSend;
    SynchronizedQueue<Request*> inQueue;
    SynchronizedQueue<Serializable*> outQueue;
    ClientLogic clientLogic;
    ClientInOutAction clientInOutAction;

public:

    explicit Client(int);

    bool isReadyToReceive();

    bool isReadyToSend();

    int getFd() const;

    void stop();

    void receive();

    void send();
};


#endif //SERVER_CLIENT_H
