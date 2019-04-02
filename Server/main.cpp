#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <cstring>
#include <zconf.h>
#include <pthread.h>
#include <vector>
#include <poll.h>
#include "ServerSocket.h"
#include "SynchronizedVector.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
using namespace std;

void *connectionListener(void *args) {
    while (true) {
        auto sockets = static_cast<SynchronizedVector<int> *>(args);
        ServerSocket serverSocket(9999);
        cout << serverSocket.getPort() << flush;
        int clientSocket = serverSocket.acceptConnection();
        sockets->put(clientSocket);
    }
}

void *dataHandler(void *args) {
    auto sockets = static_cast<SynchronizedVector<int> *>(args);
    do {
        cout << sockets->getSize() << flush;
        auto tmpSockets = sockets->getAll();
        auto numberOfSockets = tmpSockets->size();
        struct pollfd pollList[numberOfSockets];
        for (auto i = 0; i < numberOfSockets; ++i) {
            pollList[i].fd = tmpSockets->at(i);
            pollList[i].events = POLLIN;
        }
        auto retval = poll(pollList, numberOfSockets, 200);
        if (retval < 0) {
            fprintf(stderr, "Error while polling: %s\n", strerror(errno));
            return nullptr;
        }
        for (auto i = 0; i < numberOfSockets; ++i) {
            if (((pollList[i].revents & POLLHUP) == POLLHUP) ||
                ((pollList[i].revents & POLLERR) == POLLERR) ||
                ((pollList[i].revents & POLLNVAL) == POLLNVAL))
                return nullptr;
        }
        for (auto i = 0; i < numberOfSockets; ++i) {
            if ((pollList[i].revents & POLLIN) == POLLIN) {
                char buf[1024];
                ssize_t rval;
                memset(buf, 0, sizeof buf);
                if ((rval = read(pollList[i].fd, buf, 1024)) == -1)
                    perror("reading stream message");
                if (rval == 0) {
                    printf("Ending connection\n");
                    sockets->erase(pollList[i].fd);
                }
                else
                    printf("%d-->%s\n", pollList[i].fd, buf);
                fflush(stdout);
            }
        }
    } while (true);
}

int main() {
    auto *sockets = new SynchronizedVector<int>();
    pthread_t listenerThread, dataHandlerThread;
    pthread_create(&listenerThread, nullptr, connectionListener, sockets);
    pthread_create(&dataHandlerThread, nullptr, dataHandler, sockets);
    pthread_join(listenerThread, nullptr);
    pthread_join(dataHandlerThread, nullptr);
    cout << sockets->get(0) << flush;
    cout << "Hello, World!" << endl;
    return 0;
}


#pragma clang diagnostic pop