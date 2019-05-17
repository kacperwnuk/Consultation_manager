//
// Created by Marcin on 15.04.2019.
//

#define BUFFER_SIZE 1024

#include <iostream>
#include <vector>
#include <sys/poll.h>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include "TCPThread.h"
#include "../ServerSocket.h"
#include "../ClientMessageBuilder.h"
#include "../Message.h"
#include "../containers/synchronizedcontainers/MutualExclusiveHashMap.h"
#include "ClientLogic.h"

void TCPThread::run() {
    ServerSocket serverSocket(port);

    bool isRunning = true;
    do {
        auto socketInitialized = serverSocket.initialize();
        auto socketsToPoll = clients.size();
        auto serverSocketPosition = clients.size();
        pollfd pollList[socketsToPoll + 1]; //clients fds
        preparePoll(pollList);
        if (socketInitialized) {
            pollList[serverSocketPosition].fd = serverSocket.getServerSocket();
            pollList[serverSocketPosition].events = POLLIN;
            socketsToPoll++;
        }
        executePoll(pollList, socketsToPoll, socketInitialized ? -1 : 60);

        serveClients(pollList);

        acceptNewConnections(pollList, serverSocketPosition);


    } while (isRunning);

}

TCPThread::TCPThread(in_port_t port) : port(
        port) {
    pipe(pipefd);
}

void TCPThread::executePoll(pollfd pollList[], nfds_t size, int timeout) {
    auto retval = poll(pollList, size, timeout);
    if (retval < 0) {
        fprintf(stderr, "Error while polling: %s\n", strerror(errno));
        return;
    }
//    for (auto i = 0; i < numberOfSockets; ++i) {
//        if (((pollList[i].revents & POLLHUP) == POLLHUP) ||
//            ((pollList[i].revents & POLLERR) == POLLERR) ||
//            ((pollList[i].revents & POLLNVAL) == POLLNVAL))
//            return;
//    }
}

void TCPThread::serveClients(pollfd *pollList) {

    auto numberOfClients = clients.size();
    for (auto i = 0; i < numberOfClients; ++i) {
        if ((pollList[i].revents & POLLHUP) == POLLHUP) { // client closed connection
            clients[i]->stop();
            delete clients[i];
            clients.erase(clients.begin() + i);
            std::cout << "disconnect client" << std::endl;
        } else if ((pollList[i].revents & POLLIN) == POLLIN) { // client sent data
                clients[i]->receive();
        } else if ((pollList[i].revents & POLLOUT) == POLLOUT) {
                clients[i]->send();
        }
    }
}

TCPThread::~TCPThread() {

}

void TCPThread::preparePoll(pollfd *pollList) {
    for (int i = 0; i < clients.size(); ++i) {
        if (clients[i]->isConnected()) {
            clients[i]->registerActions(&pollList[i]);
        } else {
            clients[i]->stop();
            delete clients[i];
            clients.erase(clients.begin() + i);
            std::cout << "disconnect client" << std::endl;
        }
    }
}

void TCPThread::acceptNewConnections(pollfd *pollList, size_t serverSocketPosition) {
    if ((pollList[serverSocketPosition].revents & POLLIN) == POLLIN) { // new connection
        auto clientSocket = accept(pollList[serverSocketPosition].fd, (struct sockaddr *) nullptr, (socklen_t *) nullptr);
        if (clientSocket != -1) {
            std::cout << "accept client" << std::endl;
            auto *client = new Client(clientSocket);
            clients.push_back(client);
        }
    }
}



