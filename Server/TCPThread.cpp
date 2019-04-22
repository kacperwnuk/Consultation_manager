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
#include "ClientMessageBuilder.h"
#include "Message.h"
#include "containers/synchronizedcontainers/MutualExclusiveHashMap.h"
#include "ClientLogic.h"

void TCPThread::run() {
    ServerSocket serverSocket(port);
    MutualExclusiveHashMap<size_t> readDemands;
    sockets.push_back(serverSocket.getServerSocket());
    bool isRunning = true;
    do {
        auto numberOfSockets = sockets.size();
        struct pollfd pollList[numberOfSockets];

        executePoll(pollList);

        if ((pollList[0].revents & POLLIN) == POLLIN) { // new connection
            auto clientSocket = accept(pollList[0].fd, (struct sockaddr *) nullptr, (socklen_t *) nullptr);
            if (clientSocket != -1) {
                sockets.push_back(clientSocket);
                prepareClientHandler(clientSocket, readDemands);
            }
        }

        serveClient(pollList, readDemands);

    } while (isRunning);

}

TCPThread::TCPThread(in_port_t port, const std::shared_ptr<SynchronizedQueue<OutgoingMessage>> &messageQueue) : port(port), messageQueue(messageQueue) {
}

void TCPThread::executePoll(pollfd pollList[]) {
    auto numberOfSockets = sockets.size();
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
}


void TCPThread::serveClient(pollfd pollList[], MutualExclusiveHashMap<size_t> &readDemands) {

    auto numberOfSockets = sockets.size();
    for (auto i = 1; i < numberOfSockets; ++i) {
        if ((pollList[i].revents & POLLHUP) == POLLHUP) { // client closed connection
            closeSocket(pollList[i].fd);
        } else if ((pollList[i].revents & POLLIN) == POLLIN) { // client sent data
            auto client = clients[pollList[i].fd]->deserializer->clientMessageBuilder;
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
                    if (client->gettingHeader) {
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
}


void TCPThread::closeSocket(int socket) {
    auto position = std::find(sockets.begin(), sockets.end(), socket);
    clients[socket]->cancel();
    clients[socket]->join();
    clients.erase(socket);
    sockets.erase(position);
    close(socket);
}

TCPThread::~TCPThread() {
    for (auto &socket: sockets) {
        close(socket);
    }
    stopClientHandlers();
}

void TCPThread::prepareClientHandler(int socket, MutualExclusiveHashMap<size_t> &readDemands) {
    readDemands.put(socket, 0);
    auto *clientLogic = new ClientLogic(socket, readDemands, messageQueue);
    clients[socket] = clientLogic;
    clientLogic->start();
}

void TCPThread::stopClientHandlers() {
    std::cout << "Stopping client threads..." << std::endl;
    for (auto &client: clients) {
        client.second->cancel();
        client.second->join();
    }
}



