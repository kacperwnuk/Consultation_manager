//
// Created by Marcin on 15.04.2019.
//

#ifndef SERVER_TCPTHREAD_H
#define SERVER_TCPTHREAD_H

#include <netinet/in.h>
#include "Thread.h"
#include "../Client.h"
#include "../ServerSocket.h"


class TCPThread : public Thread {
private:

    int pipefd[2];

    in_port_t port;
    ServerSocket serverSocket;
    std::vector<Client*> clients;

    void executePoll(pollfd[], nfds_t , int);

    void serveClients(pollfd pollList[]);

    void servePipe(pollfd pollList[], int);

    void preparePoll(pollfd*);

    void acceptNewConnections(pollfd*, size_t);

public:
    explicit TCPThread(in_port_t);

    ~TCPThread();

    void run() override;

    void changePort(in_port_t);

};


#endif //SERVER_TCPTHREAD_H
