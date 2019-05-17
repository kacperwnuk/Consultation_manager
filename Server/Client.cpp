//
// Created by Marcin on 14.05.2019.
//

#include "Client.h"

Client::Client(int fd): clientLogic(inQueue, outQueue, wantsToWrite), clientInOutAction(fd, inQueue, outQueue, wantsToWrite, connected) {
    this->fd = fd;
    clientLogic.start();
}

void Client::stop() {
    close(fd);
    clientLogic.cancel();
}

void Client::receive() {
    clientInOutAction.receive();
}

void Client::send() {
    clientInOutAction.send();
}

bool Client::isConnected() {
    return connected;
}

void Client::registerActions(pollfd *pollListEntry) {
    pollListEntry->fd = fd;
    pollListEntry->events = POLLHUP;
    if (wantsToRead) {
        pollListEntry->events |= POLLIN;
    }
    if (wantsToWrite) {
        pollListEntry->events |= POLLOUT;
    }
}
