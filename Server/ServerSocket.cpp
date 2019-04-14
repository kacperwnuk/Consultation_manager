//
// Created by Marcin on 02.04.2019.
//

#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include "ServerSocket.h"

ServerSocket::ServerSocket(in_port_t port) {
    socklen_t length = sizeof serverAddress;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("opening stream serverSocket");
        exit(1);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, length) == -1) {
        perror("binding stream serverSocket");
        exit(1);
    }

    if (getsockname(serverSocket, (struct sockaddr *) &serverAddress, &length)
        == -1) {
        perror("getting serverSocket name");
        exit(1);
    }
    this->port = ntohs(serverAddress.sin_port);
    listen(serverSocket, 5);
}

int ServerSocket::acceptConnection() {
    struct pollfd inputConnection;
    inputConnection.fd = serverSocket;
    inputConnection.events = POLLIN;
    auto retval = poll(&inputConnection, 1, 200);
    if (retval >= 0) {
        if ((inputConnection.revents & POLLIN) == POLLIN) {
            int clientSocket = accept(serverSocket, (struct sockaddr *) nullptr, (socklen_t *) nullptr);
            if (clientSocket == -1)
                perror("acceptConnection");
            return clientSocket;
        }
    }
    return -1;
}

ServerSocket::~ServerSocket() {
    close(serverSocket);
}

in_port_t ServerSocket::getPort() {
    return port;
}
