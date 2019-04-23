//
// Created by Marcin on 15.04.2019.
//

#ifndef SERVER_TCPTHREAD_H
#define SERVER_TCPTHREAD_H

#include <netinet/in.h>
#include "Thread.h"
#include <unordered_map>
#include <memory>
#include "../containers/synchronizedcontainers/SynchronizedQueue.h"
#include "../Message.h"
#include "../containers/synchronizedcontainers/MutualExclusiveHashMap.h"
#include "../ClientMessageBuilder.h"
#include "ClientLogic.h"


class TCPThread : public Thread {
private:
    in_port_t port;
    std::vector<int> sockets;
    std::unordered_map<int, ClientLogic *> clients;
    std::shared_ptr<SynchronizedQueue<OutgoingMessage>> messageQueue;

    void closeSocket(int);

    void prepareClientHandler(int socket, MutualExclusiveHashMap<size_t> &);

    void stopClientHandlers();

    void executePoll(pollfd[]);

    void serveClient(pollfd[], MutualExclusiveHashMap<size_t> &);

public:
    TCPThread(in_port_t, const std::shared_ptr<SynchronizedQueue<OutgoingMessage>> &);

    ~TCPThread();

    void run() override;


};


#endif //SERVER_TCPTHREAD_H
