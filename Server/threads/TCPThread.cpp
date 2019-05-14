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
        auto *pollList = new pollfd[socketsToPoll + 1];
        preparePoll(pollList);
        if (socketInitialized) {
            pollList[serverSocketPosition].fd = serverSocket.getServerSocket();
            pollList[serverSocketPosition].events = POLLIN;
            socketsToPoll++;
        }
        executePoll(pollList, socketsToPoll, socketInitialized ? -1 : 60);

        acceptNewConnections(pollList, serverSocketPosition);

        serveClients(pollList);

        delete[] pollList;

    } while (isRunning);

}

TCPThread::TCPThread(in_port_t port) : port(
        port) {
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
        pollList[i].fd = clients[i]->getFd();
        pollList[i].events = POLLHUP;
        if (clients[i]->isReadyToReceive()) {
            pollList[i].events |= POLLIN;
        }
        if (clients[i]->isReadyToSend()) {
            pollList[i].events |= POLLOUT;
        }
    }
}

void TCPThread::acceptNewConnections(pollfd *pollList, size_t serverSocketPosition) {
    if ((pollList[serverSocketPosition].revents & POLLIN) == POLLIN) { // new connection
        auto clientSocket = accept(pollList[serverSocketPosition].fd, (struct sockaddr *) nullptr, (socklen_t *) nullptr);
        if (clientSocket != -1) {
            auto *client = new Client(clientSocket);
            clients.push_back(client);
        }
    }
}



