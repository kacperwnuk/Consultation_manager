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
#include <map>
#include "ServerSocket.h"
#include "SynchronizedVector.h"
#include "ThreadArgs.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
using namespace std;

enum StringValue {
    stopCommand,
    restartCommand
};
std::map<std::string, StringValue> s_mapStringValues;

void initialize() {
    s_mapStringValues["stop"] = stopCommand;
    s_mapStringValues["restart"] = restartCommand;
}

//constexpr unsigned int hash(const char *str, int h = 0) {
//    return !str[h] ? 5381 : (::hash(str, h + 1) * 33) ^ str[h];
//}

void *connectionListener(void *args) {
    auto *threadArgs = static_cast<ThreadArgs *>(args);
    auto sockets = threadArgs->getSockets();
    auto stopCond = threadArgs->getStopCond();
    while (*stopCond) {
        ServerSocket serverSocket(9999);
        int clientSocket;
        if ((clientSocket = serverSocket.acceptConnection()) != -1) {
            sockets->put(clientSocket);
        }
    }
    cout << "Listener stopped" << endl;
}

void *dataHandler(void *args) {
    auto *threadArgs = static_cast<ThreadArgs *>(args);
    auto sockets = threadArgs->getSockets();
    auto stopCond = threadArgs->getStopCond();
    do {
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
                    close(pollList[i].fd);
                } else
                    printf("%d-->%s\n", pollList[i].fd, buf);
                fflush(stdout);
            }
        }
    } while (*stopCond);
    cout << "data handler stopped" << endl;
}

int main() {
    auto *sockets = new SynchronizedVector<int>();
    auto *listenerRunning = new bool(true);
    auto *dataHandlerRunning = new bool(true);
    auto running = true;
    ThreadArgs listenerThreadArgs(sockets, listenerRunning);
    ThreadArgs dataHandlerThreadArgs(sockets, dataHandlerRunning);
    pthread_t listenerThread, dataHandlerThread, adminConsoleThread;
    pthread_create(&listenerThread, nullptr, connectionListener, &listenerThreadArgs);
    pthread_create(&dataHandlerThread, nullptr, dataHandler, &dataHandlerThreadArgs);
    initialize();
    char value[256];
    while (running) {
        cin >> value;
        switch (s_mapStringValues[value]) {
            case stopCommand:
                *listenerRunning = false;
                *dataHandlerRunning = false;
                cout << "Stopping" << endl;
                running = false;
                break;
            default:
                break;
        }
    }
    pthread_join(listenerThread, nullptr);
    pthread_join(dataHandlerThread, nullptr);
    return 0;
}


#pragma clang diagnostic pop