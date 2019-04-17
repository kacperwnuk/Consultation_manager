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
#include "ServerSocket.h"
#include "ClientMessageBuilderThread.h"
#include "IncomingMessage.h"
#include "containers/synchronizedcontainers/MutualExclusiveHashMap.h"

void TCPThread::run() {
    ServerSocket serverSocket(port);
    MutualExclusiveHashMap<size_t> readDemands;
    sockets.push_back(serverSocket.getServerSocket());
    bool isRunning = true;
    do {
        auto numberOfSockets = sockets.size();
        struct pollfd pollList[numberOfSockets];
        for (auto i = 0; i < numberOfSockets; ++i) {
            pollList[i].fd = sockets[i];
            pollList[i].events = POLLIN | POLLHUP;
        }
        auto retval = poll(pollList, numberOfSockets, -1);
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
                prepareClientHandlers(clientSocket, readDemands);
            }
        }
        for (auto i = 1; i < numberOfSockets; ++i) {
            if ((pollList[i].revents & POLLHUP) == POLLHUP) { // client closed connection
                closeSocket(pollList[i].fd);
            }
            else if ((pollList[i].revents & POLLIN) == POLLIN) { // client sent data
                auto *client = clients[pollList[i].fd];
                char buf[BUFFER_SIZE];
                ssize_t rval;
                memset(buf, 0, sizeof buf);
                pthread_mutex_lock(&(client->mutex));
                auto demand = readDemands.get(pollList[i].fd);
                if (demand > 0) {
                    if ((rval = read(pollList[i].fd, buf, demand < BUFFER_SIZE ? demand : BUFFER_SIZE)) == -1) {
                        perror("reading stream message");
                    }
                    if (rval == 0) { // client closed connection
                        printf("Ending connection\n");
                        closeSocket(pollList[i].fd);
                    } else { //client sent something
                        readDemands.put(pollList[i].fd, demand - rval);
//                        printf("%d-->%s\n", pollList[i].fd, buf);

                        if (!client->duringBuilding) {
                            memcpy(client->header + client->size, buf, rval);
                        } else {
                            memcpy(client->payload + client->size, buf, rval);
                        }
                        client->size += rval;
                        if (client->size == client->demand) {
                            pthread_cond_signal(&client->readComplete);
                        }
                    }
                    fflush(stdout);
                }
                pthread_mutex_unlock(&(client->mutex));
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
void TCPThread::prepareClientHandlers(int socket, MutualExclusiveHashMap<size_t> &readDemands) {
//    (this->clientMessageBuffers)[socket] = std::make_shared<SynchronizedQueue<IncomingMessage>>();
    readDemands.put(socket, 0);
    ClientMessageBuilderThread *clientMessageBuilderThread = new ClientMessageBuilderThread(socket, (this->clientMessageBuffers)[socket], readDemands);
    clients[socket] = clientMessageBuilderThread;
    clientMessageBuilderThread->start();
}
