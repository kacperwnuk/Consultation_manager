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
    this->port = port;
}

ServerSocket::~ServerSocket() {
    close(serverSocket);
}

in_port_t ServerSocket::getPort() {
    return port;
}

int ServerSocket::getServerSocket() {
    return serverSocket;
}

void ServerSocket::prepareServerAddress() {
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
}

bool ServerSocket::bindSocket() {
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof serverAddress) == -1) {
        perror("binding stream serverSocket");
        printf("%s", "Retrying in 60 seconds...");
        return false;
    }
    return true;
}

bool ServerSocket::createSocket() {
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("opening stream serverSocket");
        printf("%s", "Retrying in 60 seconds...");
        return false;
    }
    return true;
}

bool ServerSocket::startListening() {
    if (listen(serverSocket, 5) == -1) {
        perror("error preparing to listen");
        printf("%s", "Retrying in 60 seconds...");
        return false;
    }
    return true;
}

bool ServerSocket::getSocketName() {
    socklen_t length = sizeof serverAddress;
    if (getsockname(serverSocket, (struct sockaddr *) &serverAddress, &length) == -1) {
        perror("getting serverSocket name");
        printf("%s", "Retrying in 60 seconds...");
        return false;
    }
    return true;
}

bool ServerSocket::initialize() {
    if (!isInitialized) {
        prepareServerAddress();
        isInitialized = createSocket() && bindSocket() && getSocketName() && startListening();
        this->port = ntohs(serverAddress.sin_port);
    }
    return isInitialized;
}

void ServerSocket::changePort(in_port_t newPort) {
    close(port);
    port = newPort;
    isInitialized = false;
}
