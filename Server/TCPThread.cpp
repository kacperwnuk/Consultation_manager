//
// Created by Marcin on 15.04.2019.
//

#include <iostream>
#include <vector>
#include <sys/poll.h>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include "TCPThread.h"
#include "ServerSocket.h"
#include "ClientMessageBuilderThread.h"
#include "IncomingMessage.h"

void TCPThread::run() {
    ServerSocket serverSocket(port);
    sockets.push_back(serverSocket.getServerSocket());
    bool isRunning = true;
    do {
        auto numberOfSockets = sockets.size();
        struct pollfd pollList[numberOfSockets];
        for (auto i = 0; i < numberOfSockets; ++i) {
            pollList[i].fd = sockets[i];
            pollList[i].events = POLLIN | POLLHUP;
        }
        auto retval = poll(pollList, numberOfSockets, 0);
        if (retval < 0) {
            fprintf(stderr, "Error while polling: %s\n", strerror(errno));
            return;
        }
        for (auto i = 0; i < numberOfSockets; ++i) {
            if (((pollList[i].revents & POLLHUP) == POLLHUP) ||
                ((pollList[i].revents & POLLERR) == POLLERR) ||
                ((pollList[i].revents & POLLNVAL) == POLLNVAL))
                return;
        }
        if ((pollList[0].revents & POLLIN) == POLLIN) { // new connection
            auto clientSocket = accept(pollList[0].fd, (struct sockaddr *) nullptr, (socklen_t *) nullptr);
            if (clientSocket != -1) {
                sockets.push_back(clientSocket);
                std::cout<<"tworze nowego"<<std::endl;
                prepareClientHandlers(clientSocket);
            }
        }
        for (auto i = 1; i < numberOfSockets; ++i) {
            if ((pollList[i].revents & POLLHUP) == POLLHUP) { // client closed connection
                closeSocket(pollList[i].fd);
            }
            else if ((pollList[i].revents & POLLIN) == POLLIN) { // client sent data
                char buf[1024];
                ssize_t rval;
                memset(buf, 0, sizeof buf);
                if ((rval = read(pollList[i].fd, buf, 1024)) == -1)
                    perror("reading stream message");
                if (rval == 0) { // client closed connection
                    printf("Ending connection\n");
                    closeSocket(pollList[i].fd);
                } else { //client sent something
                    printf("%d-->%s\n", pollList[i].fd, buf);
                    IncomingMessage incomingMessage(rval, buf);
                    (*clientMessageBuffers[pollList[i].fd]).put(incomingMessage);
                }
                fflush(stdout);
            }
        }
    } while (isRunning);
}

TCPThread::TCPThread(in_port_t port) {
    this->port = port;
}

void TCPThread::closeSocket(int socket) {
    auto position = std::find(sockets.begin(), sockets.end(), socket);
    sockets.erase(position);
    close(socket);
}

TCPThread::~TCPThread() {
    for (auto &socket: sockets) {
        close(socket);
    }
}

//Create new queue for client and handler to read messages from it
void TCPThread::prepareClientHandlers(int socket) {
    (this->clientMessageBuffers)[socket] = std::make_shared<SynchronizedQueue<IncomingMessage>>();
    ClientMessageBuilderThread clientMessageBuilderThread = ClientMessageBuilderThread(socket, (this->clientMessageBuffers)[socket]);
    clientMessageBuilderThread.start();
}
