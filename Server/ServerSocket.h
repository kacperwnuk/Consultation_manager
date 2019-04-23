//
// Created by Marcin on 02.04.2019.
//

#ifndef SERVER_SERVERSOCKET_H
#define SERVER_SERVERSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class ServerSocket {
private:
    in_port_t port;
    int serverSocket;
    struct sockaddr_in serverAddress;

    void prepareServerAddress();

    void bindSocket();

    void createSocket();

    void getSocketName();

    void startListening();

public:
    explicit ServerSocket(in_port_t = 0);

    ~ServerSocket();

    in_port_t getPort();

    int getServerSocket();
};


#endif //SERVER_SERVERSOCKET_H
