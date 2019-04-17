//
// Created by Marcin on 15.04.2019.
//

#ifndef SERVER_TCPTHREAD_H
#define SERVER_TCPTHREAD_H

#include <netinet/in.h>
#include "Thread.h"
#include <unordered_map>
#include <memory>
#include "containers/synchronizedcontainers/SynchronizedQueue.h"
#include "IncomingMessage.h"


class TCPThread: public Thread {
private:
    in_port_t port;
    std::vector<int> sockets;
    std::unordered_map<int, std::shared_ptr<SynchronizedQueue<IncomingMessage>>> clientMessageBuffers;
    void closeSocket(int);
    void prepareClientHandlers(int socket);
public:
    explicit TCPThread(in_port_t port);
    ~TCPThread();
    void run() override;


};


#endif //SERVER_TCPTHREAD_H
