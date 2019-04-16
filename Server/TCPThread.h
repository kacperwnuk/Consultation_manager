//
// Created by Marcin on 15.04.2019.
//

#ifndef SERVER_TCPTHREAD_H
#define SERVER_TCPTHREAD_H

#include <netinet/in.h>
#include "Thread.h"

class TCPThread: public Thread {
private:
    in_port_t port;
    std::vector<int> sockets;
    void closeSocket(int);
public:
    explicit TCPThread(in_port_t port);
    ~TCPThread();
    void run() override;
};


#endif //SERVER_TCPTHREAD_H
